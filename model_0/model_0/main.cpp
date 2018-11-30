#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "WAVheader.h"
#include "tremolo2.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define BLOCK_SIZE 16
#define MAX_NUM_CHANNEL 2
#define MAX_NUM_CHANNEL_MODE2 4

double sampleBuffer[MAX_NUM_CHANNEL_MODE2][BLOCK_SIZE];
const double dB2double = 0.630957;
tremolo_struct_t tremolo;
bool mode = true;

bool check_mode() {
	return (mode == true) ? true : false;
}

void processing()
{
	init(&tremolo);
	int i, j;
	double* left_in = sampleBuffer[0];
	double* right_in = sampleBuffer[1];
	double* left_out = sampleBuffer[0];
	double* right_out = sampleBuffer[1];
	double* lsOutput = sampleBuffer[2];
	double* rsOutput = sampleBuffer[3];

	for (i = 0; i < BLOCK_SIZE; i++)
	{
		*left_out = (*left_in) * dB2double;
		*right_out = (*right_in) * dB2double;
	}
	
	if (check_mode() == true) 
	{
		for (i = 0; i < BLOCK_SIZE; i++)
		{
			*lsOutput = *left_in * dB2double;
			processBlock(lsOutput, lsOutput, &tremolo, BLOCK_SIZE);

			*rsOutput = *right_in * dB2double;
			processBlock(rsOutput, rsOutput, &tremolo, BLOCK_SIZE);
		}		
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
	for (int i = 0; i<MAX_NUM_CHANNEL_MODE2; i++)
		memset(&sampleBuffer[i], 0, BLOCK_SIZE);

	// Open input and output wav files
	//-------------------------------------------------
	strcpy_s(WavInputName, argv[1]);
	wav_in = OpenWavFileForRead(WavInputName, "rb");	
	strcpy_s(WavOutputName, argv[2]);
	wav_out = OpenWavFileForRead(WavOutputName, "wb");
	//-------------------------------------------------
	mode = (argv[3] == 0) ? true : false;
	// Read input wav header
	//-------------------------------------------------
	ReadWavHeader(wav_in, inputWAVhdr);
	//-------------------------------------------------

	// Set up output WAV header
	//-------------------------------------------------	
	outputWAVhdr = inputWAVhdr;
	outputWAVhdr.fmt.NumChannels = inputWAVhdr.fmt.NumChannels; // change number of channels

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