cd model_0\Debug

"model_0.exe" "C:\Users\Uros\Desktop\AADSP2-projekat\cirrus_logic_dsp_tremolo\TestStreams\Amp_Sweep.wav" "C:\Users\Uros\Desktop\AADSP2-projekat\cirrus_logic_dsp_tremolo\OutStreams\output_model_0.wav" "1"

cd ..\..

cd model_1\Debug

"model_1.exe" "C:\Users\Uros\Desktop\AADSP2-projekat\cirrus_logic_dsp_tremolo\TestStreams\Amp_Sweep.wav" "C:\Users\Uros\Desktop\AADSP2-projekat\cirrus_logic_dsp_tremolo\OutStreams\output_model_1.wav" "1"

cd ..\..

cd model_2\Debug

"model_2.exe" "C:\Users\Uros\Desktop\AADSP2-projekat\cirrus_logic_dsp_tremolo\TestStreams\Amp_Sweep.wav" "C:\Users\Uros\Desktop\AADSP2-projekat\cirrus_logic_dsp_tremolo\OutStreams\output_model_2.wav" "1"

cd ..\..

PCMCompare "C:\Users\Uros\Desktop\AADSP2-projekat\cirrus_logic_dsp_tremolo\OutStreams\output_model_0.wav" "C:\Users\Uros\Desktop\AADSP2-projekat\cirrus_logic_dsp_tremolo\OutStreams\output_model_1.wav" > C:\Users\Uros\Desktop\AADSP2-projekat\cirrus_logic_dsp_tremolo\logs\cmp0vs1.txt
PCMCompare "C:\Users\Uros\Desktop\AADSP2-projekat\cirrus_logic_dsp_tremolo\OutStreams\output_model_1.wav" "C:\Users\Uros\Desktop\AADSP2-projekat\cirrus_logic_dsp_tremolo\OutStreams\output_model_2.wav" > C:\Users\Uros\Desktop\AADSP2-projekat\cirrus_logic_dsp_tremolo\logs\cmp1vs2.txt

pause