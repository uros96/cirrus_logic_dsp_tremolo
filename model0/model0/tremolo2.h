#pragma once

#include <math.h>
#define SAMPLE_RATE 48000
#define BLOCK_SIZE 16
#define PI 3.14159265358979323846

typedef struct {
	int numChannels;

	float LFO_frequency;  // LFO frequency (Hz)

	float depth;      // Depth of effect (0-1)

	float lfoPhase;

	float inverseSampleRate;
} tremolo_struct_t;

float gen_sine_wave(float phase);
void init(tremolo_struct_t * data);
void processBlock(double* input, double* output, tremolo_struct_t* data, int numSamples);

// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

#include <SDKDDKVer.h>
