"model_0\Debug\model_0.exe" "TestStreams\Amp_Sweep.wav" "OutStreams\output_model_0.wav" "0"
"model_1\Debug\model_1.exe" "TestStreams\Amp_Sweep.wav" "OutStreams\output_model_0.wav" "0"
"model_2\Debug\model_2.exe" "TestStreams\Amp_Sweep.wav" "OutStreams\output_model_2.wav" "0"

:PCMCompare "OutStreams\output_model_0.wav" "OutStreams\output_model_1.wav" > logs\cmp0vs1.txt
:PCMCompare "OutStreams\output_model_1.wav" "OutStreams\output_model_2.wav" > logs\cmp1vs2.txt
PCMCompare "OutStreams\output_model_0.wav" "OutStreams\output_model_2.wav" > logs\cmp0vs2.txt

pause