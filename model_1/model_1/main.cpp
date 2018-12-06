#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "WAVheader.h"
#include "tremolo2.h"
#include "stdafx.h"
#include "common.h"

double sampleBuffer[MAX_NUM_CHANNEL][BLOCK_SIZE];
double dB2double = 0.630957;
tremolo_struct_t tremolo;
enum mode_t
{ 
	MODE_0, 
	MODE_1 
};

mode_t mode = MODE_0;

void processing()
{
	//DSPfract* p;
	int i;
//	for (p = *sampleBuffer; p < *sampleBuffer + BLOCK_SIZE; p++) 
//	{
//		*p = *p * dB2double;
//		*(p+16) = *(p+16) * dB2double;
//	}
	
	double* left_in = sampleBuffer[0];
	double* right_in = sampleBuffer[1];
	double* left_out = sampleBuffer[0];
	double* right_out = sampleBuffer[1];
	double* left_s_out = sampleBuffer[2];
	double* right_s_out = sampleBuffer[3];

	for (i = 0; i < BLOCK_SIZE; i++)
	{
		*left_out = *left_in * dB2double;
		*right_out = *right_out * dB2double;

		left_in++;
		left_out++;
		right_in++;
		right_out++;
	}

	left_out -= BLOCK_SIZE;
	right_out -= BLOCK_SIZE;

	if (mode == MODE_1)
	{
		processBlock(left_out, left_s_out, &tremolo, BLOCK_SIZE);
		processBlock(right_out, right_s_out, &tremolo, BLOCK_SIZE);
	}
}

int main(int argc, char* argv[])
{
	FILE *wav_in = NULL;
	FILE *wav_out = NULL;
	char WavInputName[256];
	char WavOutputName[256];
	WAV_HEADER inputWAVhdr;
	WAV_HEADER outputWAVhdr;

	// Init channel buffers
	for (int i = 0; i<MAX_NUM_CHANNEL; i++)
		memset(&sampleBuffer[i], 0, BLOCK_SIZE);

	// Open input and output wav files
	//-------------------------------------------------
	strcpy_s(WavInputName, argv[1]);
	wav_in = OpenWavFileForRead(WavInputName, "rb");	
	strcpy_s(WavOutputName, argv[2]);
	wav_out = OpenWavFileForRead(WavOutputName, "wb");
	//-------------------------------------------------

	mode = ((argc >= 4) && (atoi(argv[3]) == 0)) ? MODE_0 : MODE_1;
	dB2double = (argc >= 5) ? pow(10, atoi(argv[4])/20) : 0.630957;

	// Read input wav header
	//-------------------------------------------------
	ReadWavHeader(wav_in, inputWAVhdr);
	//-------------------------------------------------

	// Set up output WAV header
	//-------------------------------------------------	
	outputWAVhdr = inputWAVhdr;
//	outputWAVhdr.fmt.NumChannels = inputWAVhdr.fmt.NumChannels; // change number of channels
	outputWAVhdr.fmt.NumChannels = (mode == MODE_0) ? 2 : 4; // change number of channels

	int oneChannelSubChunk2Size = inputWAVhdr.data.SubChunk2Size / inputWAVhdr.fmt.NumChannels;
	int oneChannelByteRate = inputWAVhdr.fmt.ByteRate / inputWAVhdr.fmt.NumChannels;
	int oneChannelBlockAlign = inputWAVhdr.fmt.BlockAlign / inputWAVhdr.fmt.NumChannels;

	outputWAVhdr.data.SubChunk2Size = oneChannelSubChunk2Size*outputWAVhdr.fmt.NumChannels;
	outputWAVhdr.fmt.ByteRate = oneChannelByteRate*outputWAVhdr.fmt.NumChannels;
	outputWAVhdr.fmt.BlockAlign = oneChannelBlockAlign*outputWAVhdr.fmt.NumChannels;

	// Write output WAV header to file
	//-------------------------------------------------
	WriteWavHeader(wav_out, outputWAVhdr);


	// Processing loop
	//-------------------------------------------------	
	{
		int sample;
		int BytesPerSample = inputWAVhdr.fmt.BitsPerSample / 8;
		const double SAMPLE_SCALE = -(double)(1 << 31);		//2^31
		int iNumSamples = inputWAVhdr.data.SubChunk2Size / (inputWAVhdr.fmt.NumChannels*inputWAVhdr.fmt.BitsPerSample / 8);

		init(&tremolo);

		// exact file length should be handled correctly...
		for (int i = 0; i<iNumSamples / BLOCK_SIZE; i++)
		{
			for (int j = 0; j<BLOCK_SIZE; j++)
			{
				for (int k = 0; k<inputWAVhdr.fmt.NumChannels; k++)
				{
					sample = 0; //debug
					fread(&sample, BytesPerSample, 1, wav_in);
					sample = sample << (32 - inputWAVhdr.fmt.BitsPerSample); // force signextend
					sampleBuffer[k][j] = sample / SAMPLE_SCALE;				// scale sample to 1.0/-1.0 range		
				}
			}

			processing();	

			for (int j = 0; j<BLOCK_SIZE; j++)
			{
				for (int k = 0; k<outputWAVhdr.fmt.NumChannels; k++)
				{
					sample = sampleBuffer[k][j] * SAMPLE_SCALE;	// crude, non-rounding 			
					sample = sample >> (32 - inputWAVhdr.fmt.BitsPerSample);
					fwrite(&sample, outputWAVhdr.fmt.BitsPerSample / 8, 1, wav_out);
				}
			}
		}
	}

	// Close files
	//-------------------------------------------------	
	fclose(wav_in);
	fclose(wav_out);
	//-------------------------------------------------	

	return 0;
}
