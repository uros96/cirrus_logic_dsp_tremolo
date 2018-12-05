#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "WAVheader.h"
//#include "tremolo2.h"
#include <math.h>

#include "stdafx.h"
#include "common.h"

#define SAMPLE_RATE 48000
#define BLOCK_SIZE 16
#define PI 3.14159265358979323846

typedef struct {
	DSPint numChannels;

	DSPfract LFO_frequency;  // LFO frequency (Hz)

	DSPfract depth;      // Depth of effect (0-1)

	DSPfract lfoPhase;

	DSPfract inverseSampleRate;
} tremolo_struct_t;

DSPfract sampleBuffer[MAX_NUM_CHANNEL][BLOCK_SIZE];
DSPfract dB2double = 0.630957;
DSPfract* input;
DSPfract* output;
DSPfract phase;
DSPfract* left = sampleBuffer[0];
DSPfract* right = sampleBuffer[1];
DSPfract* left_s = sampleBuffer[2];
DSPfract* right_s = sampleBuffer[3];

tremolo_struct_t tremolo;
enum mode_t
{ 
	MODE_0, 
	MODE_1 
};

mode_t mode = MODE_0;

void processing();
void init();
void processBlock();
DSPfract gen_sine_wave();

DSPint main(DSPint argc, char* argv[])
{
	FILE *wav_in = NULL;
	FILE *wav_out = NULL;
	char WavInputName[256];
	char WavOutputName[256];
	WAV_HEADER inputWAVhdr;
	WAV_HEADER outputWAVhdr;

	// Init channel buffers
	for (DSPint i = 0; i<MAX_NUM_CHANNEL; i++)
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

	DSPint oneChannelSubChunk2Size = inputWAVhdr.data.SubChunk2Size / inputWAVhdr.fmt.NumChannels;
	DSPint oneChannelByteRate = inputWAVhdr.fmt.ByteRate / inputWAVhdr.fmt.NumChannels;
	DSPint oneChannelBlockAlign = inputWAVhdr.fmt.BlockAlign / inputWAVhdr.fmt.NumChannels;

	outputWAVhdr.data.SubChunk2Size = oneChannelSubChunk2Size*outputWAVhdr.fmt.NumChannels;
	outputWAVhdr.fmt.ByteRate = oneChannelByteRate*outputWAVhdr.fmt.NumChannels;
	outputWAVhdr.fmt.BlockAlign = oneChannelBlockAlign*outputWAVhdr.fmt.NumChannels;

	// Write output WAV header to file
	//-------------------------------------------------
	WriteWavHeader(wav_out, outputWAVhdr);

	init();

	// Processing loop
	//-------------------------------------------------	
	{
		DSPint sample;
		DSPint BytesPerSample = inputWAVhdr.fmt.BitsPerSample / 8;
		const DSPfract SAMPLE_SCALE = -(DSPfract)(1 << 31);		//2^31
		DSPint iNumSamples = inputWAVhdr.data.SubChunk2Size / (inputWAVhdr.fmt.NumChannels*inputWAVhdr.fmt.BitsPerSample / 8);

		// exact file length should be handled correctly...
		for (DSPint i = 0; i<iNumSamples / BLOCK_SIZE; i++)
		{
			for (DSPint j = 0; j<BLOCK_SIZE; j++)
			{
				for (DSPint k = 0; k<inputWAVhdr.fmt.NumChannels; k++)
				{
					sample = 0; //debug
					fread(&sample, BytesPerSample, 1, wav_in);
					sample = sample << (32 - inputWAVhdr.fmt.BitsPerSample); // force signextend
					sampleBuffer[k][j] = sample / SAMPLE_SCALE;				// scale sample to 1.0/-1.0 range		
				}
			}

			processing();

			for (DSPint j = 0; j<BLOCK_SIZE; j++)
			{
				for (DSPint k = 0; k<outputWAVhdr.fmt.NumChannels; k++)
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

void processing()
{
	DSPfract* p;

	for (p = *sampleBuffer; p < sampleBuffer[0] + BLOCK_SIZE; p++)
	{
		*p = *p * dB2double;
		*(p + 16) = *(p + 16) * dB2double;
	}

	if (mode == MODE_1)
	{
		input = left;
		output = left_s;
		processBlock();

		input = right;
		output = right_s;
		processBlock();
	}
}

void init() {

	// Set default values:
	tremolo.LFO_frequency = 2.0;
	tremolo.depth = 1.0;
	tremolo.lfoPhase = 0.0;
	tremolo.inverseSampleRate = 1.0 / SAMPLE_RATE;
}

void processBlock() {

//	DSPfract ph;

	// Make a temporary copy of any state variables which need to be
	// maintained between calls to processBlock(). Each channel needs to be processed identically
	// which means that the activity of processing one channel can't affect the state variable for
	// the next channel.
	phase = tremolo.lfoPhase;

	for (DSPint i = 0; i < BLOCK_SIZE; ++i)
	{
		const DSPfract in = input[i];

		// Ring modulation is easy! Just multiply the waveform by a periodic carrier
		output[i] = in * (1.0f - tremolo.depth * gen_sine_wave());

		// Update the carrier and LFO phases, keeping them in the range 0-1
		phase += tremolo.LFO_frequency * tremolo.inverseSampleRate;
		if (phase >= 1.0)
			phase -= 1.0;
	}

	// Having made a local copy of the state variables for each channel, now transfer the result
	// back to the main state variable so they will be preserved for the next call of processBlock()
	tremolo.lfoPhase = phase;
}

DSPfract gen_sine_wave()
{
	return 0.5f + 0.5f * sinf(2.0 * PI * phase);
}