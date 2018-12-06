#pragma once
#include <math.h>
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


enum mode_t
{
	MODE_0,
	MODE_1
};

DSPfract sampleBuffer[MAX_NUM_CHANNEL][BLOCK_SIZE];
DSPfract dB2double = FRACT_NUM(0.630957);
DSPfract* input;
DSPfract* output;
DSPfract phase;
DSPfract* left = sampleBuffer[0];
DSPfract* right = *(sampleBuffer + 1);
DSPfract* left_s = *(sampleBuffer + 2);
DSPfract* right_s = *(sampleBuffer + 3);
DSPaccum temp;
tremolo_struct_t tremolo;

mode_t mode = MODE_0;

DSPfract gen_sine_wave(DSPfract phase);
void init();
void processBlock();
void processing();

void processing()
{
	DSPfract* p;

	for (p = *sampleBuffer; p < *sampleBuffer + BLOCK_SIZE; p++)
	{
		*p = *p * dB2double;
//		 = temp;
		p = p + BLOCK_SIZE;
//		temp = *p * dB2double;
		*p = *p * dB2double; //temp;
		p = p - BLOCK_SIZE;
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

void init()
{
	// Set default values:
	tremolo.LFO_frequency = (DSPfract)(((DSPint)2.0) << 1);
	tremolo.depth = FRACT_NUM(1.0);
	tremolo.lfoPhase = FRACT_NUM(0.0);
	tremolo.inverseSampleRate = 1.0 / SAMPLE_RATE;
}

void processBlock()
{
	DSPfract ph;

	// Make a temporary copy of any state variables which need to be
	// maintained between calls to processBlock(). Each channel needs to be processed identically
	// which means that the activity of processing one channel can't affect the state variable for
	// the next channel.
	ph = tremolo.lfoPhase;

	for (DSPint i = 0; i < BLOCK_SIZE; ++i)
	{
		const DSPfract in = input[i];

		// Ring modulation is easy! Just multiply the waveform by a periodic carrier
		output[i] = (1.0f - tremolo.depth * gen_sine_wave(ph)) * in;
		// Update the carrier and LFO phases, keeping them in the range 0-1
		ph = ph + tremolo.LFO_frequency * tremolo.inverseSampleRate;
		if (ph >= FRACT_NUM(1.0))
			ph = ph - FRACT_NUM(1.0);
	}

	// Having made a local copy of the state variables for each channel, now transfer the result
	// back to the main state variable so they will be preserved for the next call of processBlock()
	tremolo.lfoPhase = ph;
}

//==============================================================================

DSPfract gen_sine_wave(DSPfract phase)
{
	return FRACT_NUM(0.5f + 0.5f * sinf(2.0 * PI * phase));
}
