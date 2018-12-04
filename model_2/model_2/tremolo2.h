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

//float gen_sine_wave(float phase);
//void init(tremolo_struct_t * data);
//void processBlock(double* input, double* output, tremolo_struct_t* data, int numSamples);

void init(tremolo_struct_t * data) {

	// Set default values:
	data->LFO_frequency = 2.0;
	data->depth = 1.0;
	data->lfoPhase = 0.0;
	data->inverseSampleRate = 1.0 / SAMPLE_RATE;
}

float gen_sine_wave(float phase)
{
	return 0.5f + 0.5f * sinf(2.0 * PI * phase);
}


void processBlock(double* input, double* output, tremolo_struct_t* data, int numSamples) {

	float ph;

	// Make a temporary copy of any state variables which need to be
	// maintained between calls to processBlock(). Each channel needs to be processed identically
	// which means that the activity of processing one channel can't affect the state variable for
	// the next channel.
	ph = data->lfoPhase;

	for (int i = 0; i < numSamples; ++i)
	{
		const float in = input[i];

		// Ring modulation is easy! Just multiply the waveform by a periodic carrier
		output[i] = in * (1.0f - data->depth * gen_sine_wave(ph));

		// Update the carrier and LFO phases, keeping them in the range 0-1
		ph += data->LFO_frequency * data->inverseSampleRate;
		if (ph >= 1.0)
			ph -= 1.0;
	}

	// Having made a local copy of the state variables for each channel, now transfer the result
	// back to the main state variable so they will be preserved for the next call of processBlock()
	data->lfoPhase = ph;
}

//==============================================================================


// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

//#include <SDKDDKVer.h>
