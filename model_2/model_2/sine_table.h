#pragma once

#include"common.h"
#define MAX_LOOK_UP_INDEX 511
#define TABLE_SIZE 512

DSPfract sine_table[TABLE_SIZE] =
{
	FRACT_NUM(0.500000), FRACT_NUM(0.506136), FRACT_NUM(0.512271), FRACT_NUM(0.518404), FRACT_NUM(0.524534), FRACT_NUM(0.530660), FRACT_NUM(0.536782), FRACT_NUM(0.542899),
	FRACT_NUM(0.549009), FRACT_NUM(0.555111), FRACT_NUM(0.561205), FRACT_NUM(0.567290), FRACT_NUM(0.573365), FRACT_NUM(0.579429), FRACT_NUM(0.585481), FRACT_NUM(0.591520),
	FRACT_NUM(0.597545), FRACT_NUM(0.603556), FRACT_NUM(0.609551), FRACT_NUM(0.615529), FRACT_NUM(0.621490), FRACT_NUM(0.627433), FRACT_NUM(0.633356), FRACT_NUM(0.639260),
	FRACT_NUM(0.645142), FRACT_NUM(0.651003), FRACT_NUM(0.656841), FRACT_NUM(0.662655), FRACT_NUM(0.668445), FRACT_NUM(0.674209), FRACT_NUM(0.679948), FRACT_NUM(0.685659),
	FRACT_NUM(0.691342), FRACT_NUM(0.696996), FRACT_NUM(0.702621), FRACT_NUM(0.708215), FRACT_NUM(0.713778), FRACT_NUM(0.719308), FRACT_NUM(0.724806), FRACT_NUM(0.730269),
	FRACT_NUM(0.735698), FRACT_NUM(0.741092), FRACT_NUM(0.746449), FRACT_NUM(0.751769), FRACT_NUM(0.757051), FRACT_NUM(0.762295), FRACT_NUM(0.767499), FRACT_NUM(0.772662),
	FRACT_NUM(0.777785), FRACT_NUM(0.782866), FRACT_NUM(0.787904), FRACT_NUM(0.792899), FRACT_NUM(0.797850), FRACT_NUM(0.802756), FRACT_NUM(0.807616), FRACT_NUM(0.812430),
	FRACT_NUM(0.817197), FRACT_NUM(0.821916), FRACT_NUM(0.826586), FRACT_NUM(0.831208), FRACT_NUM(0.835779), FRACT_NUM(0.840301), FRACT_NUM(0.844770), FRACT_NUM(0.849188),
	FRACT_NUM(0.853553), FRACT_NUM(0.857865), FRACT_NUM(0.862124), FRACT_NUM(0.866327), FRACT_NUM(0.870476), FRACT_NUM(0.874568), FRACT_NUM(0.878604), FRACT_NUM(0.882584),
	FRACT_NUM(0.886505), FRACT_NUM(0.890369), FRACT_NUM(0.894173), FRACT_NUM(0.897918), FRACT_NUM(0.901604), FRACT_NUM(0.905229), FRACT_NUM(0.908792), FRACT_NUM(0.912295),
	FRACT_NUM(0.915735), FRACT_NUM(0.919112), FRACT_NUM(0.922427), FRACT_NUM(0.925678), FRACT_NUM(0.928864), FRACT_NUM(0.931986), FRACT_NUM(0.935043), FRACT_NUM(0.938035),
	FRACT_NUM(0.940961), FRACT_NUM(0.943820), FRACT_NUM(0.946612), FRACT_NUM(0.949337), FRACT_NUM(0.951995), FRACT_NUM(0.954584), FRACT_NUM(0.957105), FRACT_NUM(0.959557),
	FRACT_NUM(0.961940), FRACT_NUM(0.964253), FRACT_NUM(0.966496), FRACT_NUM(0.968670), FRACT_NUM(0.970772), FRACT_NUM(0.972804), FRACT_NUM(0.974764), FRACT_NUM(0.976653),
	FRACT_NUM(0.978470), FRACT_NUM(0.980215), FRACT_NUM(0.981888), FRACT_NUM(0.983488), FRACT_NUM(0.985016), FRACT_NUM(0.986470), FRACT_NUM(0.987851), FRACT_NUM(0.989159),
	FRACT_NUM(0.990393), FRACT_NUM(0.991553), FRACT_NUM(0.992639), FRACT_NUM(0.993651), FRACT_NUM(0.994588), FRACT_NUM(0.995451), FRACT_NUM(0.996240), FRACT_NUM(0.996953),
	FRACT_NUM(0.997592), FRACT_NUM(0.998156), FRACT_NUM(0.998645), FRACT_NUM(0.999059), FRACT_NUM(0.999398), FRACT_NUM(0.999661), FRACT_NUM(0.999849), FRACT_NUM(0.999962),
	FRACT_NUM(1.000000), FRACT_NUM(0.999962), FRACT_NUM(0.999849), FRACT_NUM(0.999661), FRACT_NUM(0.999398), FRACT_NUM(0.999059), FRACT_NUM(0.998645), FRACT_NUM(0.998156),
	FRACT_NUM(0.997592), FRACT_NUM(0.996953), FRACT_NUM(0.996240), FRACT_NUM(0.995451), FRACT_NUM(0.994588), FRACT_NUM(0.993651), FRACT_NUM(0.992639), FRACT_NUM(0.991553),
	FRACT_NUM(0.990393), FRACT_NUM(0.989159), FRACT_NUM(0.987851), FRACT_NUM(0.986470), FRACT_NUM(0.985016), FRACT_NUM(0.983488), FRACT_NUM(0.981888), FRACT_NUM(0.980215),
	FRACT_NUM(0.978470), FRACT_NUM(0.976653), FRACT_NUM(0.974764), FRACT_NUM(0.972804), FRACT_NUM(0.970772), FRACT_NUM(0.968670), FRACT_NUM(0.966496), FRACT_NUM(0.964253),
	FRACT_NUM(0.961940), FRACT_NUM(0.959557), FRACT_NUM(0.957105), FRACT_NUM(0.954584), FRACT_NUM(0.951995), FRACT_NUM(0.949337), FRACT_NUM(0.946612), FRACT_NUM(0.943820),
	FRACT_NUM(0.940961), FRACT_NUM(0.938035), FRACT_NUM(0.935044), FRACT_NUM(0.931986), FRACT_NUM(0.928864), FRACT_NUM(0.925678), FRACT_NUM(0.922427), FRACT_NUM(0.919112),
	FRACT_NUM(0.915735), FRACT_NUM(0.912295), FRACT_NUM(0.908792), FRACT_NUM(0.905229), FRACT_NUM(0.901604), FRACT_NUM(0.897918), FRACT_NUM(0.894173), FRACT_NUM(0.890369),
	FRACT_NUM(0.886505), FRACT_NUM(0.882584), FRACT_NUM(0.878604), FRACT_NUM(0.874568), FRACT_NUM(0.870476), FRACT_NUM(0.866327), FRACT_NUM(0.862124), FRACT_NUM(0.857865),
	FRACT_NUM(0.853553), FRACT_NUM(0.849188), FRACT_NUM(0.844770), FRACT_NUM(0.840300), FRACT_NUM(0.835780), FRACT_NUM(0.831208), FRACT_NUM(0.826586), FRACT_NUM(0.821916),
	FRACT_NUM(0.817197), FRACT_NUM(0.812430), FRACT_NUM(0.807616), FRACT_NUM(0.802756), FRACT_NUM(0.797850), FRACT_NUM(0.792899), FRACT_NUM(0.787904), FRACT_NUM(0.782866),
	FRACT_NUM(0.777785), FRACT_NUM(0.772663), FRACT_NUM(0.767499), FRACT_NUM(0.762295), FRACT_NUM(0.757051), FRACT_NUM(0.751769), FRACT_NUM(0.746449), FRACT_NUM(0.741092),
	FRACT_NUM(0.735698), FRACT_NUM(0.730269), FRACT_NUM(0.724806), FRACT_NUM(0.719308), FRACT_NUM(0.713778), FRACT_NUM(0.708215), FRACT_NUM(0.702621), FRACT_NUM(0.696996),
	FRACT_NUM(0.691342), FRACT_NUM(0.685659), FRACT_NUM(0.679948), FRACT_NUM(0.674209), FRACT_NUM(0.668445), FRACT_NUM(0.662655), FRACT_NUM(0.656841), FRACT_NUM(0.651003),
	FRACT_NUM(0.645142), FRACT_NUM(0.639260), FRACT_NUM(0.633356), FRACT_NUM(0.627433), FRACT_NUM(0.621490), FRACT_NUM(0.615529), FRACT_NUM(0.609551), FRACT_NUM(0.603556),
	FRACT_NUM(0.597545), FRACT_NUM(0.591520), FRACT_NUM(0.585481), FRACT_NUM(0.579429), FRACT_NUM(0.573365), FRACT_NUM(0.567290), FRACT_NUM(0.561205), FRACT_NUM(0.555111),
	FRACT_NUM(0.549009), FRACT_NUM(0.542899), FRACT_NUM(0.536782), FRACT_NUM(0.530660), FRACT_NUM(0.524534), FRACT_NUM(0.518404), FRACT_NUM(0.512271), FRACT_NUM(0.506136),
	FRACT_NUM(0.500000), FRACT_NUM(0.493864), FRACT_NUM(0.487729), FRACT_NUM(0.481596), FRACT_NUM(0.475466), FRACT_NUM(0.469340), FRACT_NUM(0.463218), FRACT_NUM(0.457101),
	FRACT_NUM(0.450991), FRACT_NUM(0.444889), FRACT_NUM(0.438795), FRACT_NUM(0.432710), FRACT_NUM(0.426635), FRACT_NUM(0.420571), FRACT_NUM(0.414519), FRACT_NUM(0.408480),
	FRACT_NUM(0.402455), FRACT_NUM(0.396444), FRACT_NUM(0.390449), FRACT_NUM(0.384471), FRACT_NUM(0.378510), FRACT_NUM(0.372567), FRACT_NUM(0.366644), FRACT_NUM(0.360740),
	FRACT_NUM(0.354858), FRACT_NUM(0.348997), FRACT_NUM(0.343159), FRACT_NUM(0.337345), FRACT_NUM(0.331555), FRACT_NUM(0.325791), FRACT_NUM(0.320053), FRACT_NUM(0.314341),
	FRACT_NUM(0.308658), FRACT_NUM(0.303004), FRACT_NUM(0.297379), FRACT_NUM(0.291785), FRACT_NUM(0.286222), FRACT_NUM(0.280692), FRACT_NUM(0.275194), FRACT_NUM(0.269731),
	FRACT_NUM(0.264302), FRACT_NUM(0.258908), FRACT_NUM(0.253551), FRACT_NUM(0.248231), FRACT_NUM(0.242949), FRACT_NUM(0.237705), FRACT_NUM(0.232501), FRACT_NUM(0.227337),
	FRACT_NUM(0.222215), FRACT_NUM(0.217134), FRACT_NUM(0.212096), FRACT_NUM(0.207101), FRACT_NUM(0.202150), FRACT_NUM(0.197244), FRACT_NUM(0.192384), FRACT_NUM(0.187570),
	FRACT_NUM(0.182803), FRACT_NUM(0.178084), FRACT_NUM(0.173414), FRACT_NUM(0.168792), FRACT_NUM(0.164221), FRACT_NUM(0.159699), FRACT_NUM(0.155230), FRACT_NUM(0.150812),
	FRACT_NUM(0.146447), FRACT_NUM(0.142135), FRACT_NUM(0.137876), FRACT_NUM(0.133673), FRACT_NUM(0.129524), FRACT_NUM(0.125432), FRACT_NUM(0.121396), FRACT_NUM(0.117416),
	FRACT_NUM(0.113495), FRACT_NUM(0.109631), FRACT_NUM(0.105827), FRACT_NUM(0.102082), FRACT_NUM(0.098396), FRACT_NUM(0.094771), FRACT_NUM(0.091208), FRACT_NUM(0.087705),
	FRACT_NUM(0.084265), FRACT_NUM(0.080888), FRACT_NUM(0.077573), FRACT_NUM(0.074322), FRACT_NUM(0.071136), FRACT_NUM(0.068014), FRACT_NUM(0.064957), FRACT_NUM(0.061965),
	FRACT_NUM(0.059039), FRACT_NUM(0.056180), FRACT_NUM(0.053388), FRACT_NUM(0.050663), FRACT_NUM(0.048005), FRACT_NUM(0.045416), FRACT_NUM(0.042895), FRACT_NUM(0.040443),
	FRACT_NUM(0.038060), FRACT_NUM(0.035747), FRACT_NUM(0.033504), FRACT_NUM(0.031330), FRACT_NUM(0.029228), FRACT_NUM(0.027196), FRACT_NUM(0.025236), FRACT_NUM(0.023347),
	FRACT_NUM(0.021530), FRACT_NUM(0.019785), FRACT_NUM(0.018112), FRACT_NUM(0.016512), FRACT_NUM(0.014984), FRACT_NUM(0.013530), FRACT_NUM(0.012149), FRACT_NUM(0.010841),
	FRACT_NUM(0.009607), FRACT_NUM(0.008447), FRACT_NUM(0.007361), FRACT_NUM(0.006349), FRACT_NUM(0.005412), FRACT_NUM(0.004549), FRACT_NUM(0.003760), FRACT_NUM(0.003047),
	FRACT_NUM(0.002408), FRACT_NUM(0.001844), FRACT_NUM(0.001355), FRACT_NUM(0.000941), FRACT_NUM(0.000602), FRACT_NUM(0.000339), FRACT_NUM(0.000151), FRACT_NUM(0.000038),
	FRACT_NUM(0.000001), FRACT_NUM(0.000038), FRACT_NUM(0.000151), FRACT_NUM(0.000339), FRACT_NUM(0.000602), FRACT_NUM(0.000941), FRACT_NUM(0.001355), FRACT_NUM(0.001844),
	FRACT_NUM(0.002408), FRACT_NUM(0.003047), FRACT_NUM(0.003760), FRACT_NUM(0.004549), FRACT_NUM(0.005412), FRACT_NUM(0.006349), FRACT_NUM(0.007361), FRACT_NUM(0.008447),
	FRACT_NUM(0.009607), FRACT_NUM(0.010841), FRACT_NUM(0.012149), FRACT_NUM(0.013530), FRACT_NUM(0.014984), FRACT_NUM(0.016512), FRACT_NUM(0.018112), FRACT_NUM(0.019785),
	FRACT_NUM(0.021530), FRACT_NUM(0.023347), FRACT_NUM(0.025236), FRACT_NUM(0.027196), FRACT_NUM(0.029228), FRACT_NUM(0.031330), FRACT_NUM(0.033504), FRACT_NUM(0.035747),
	FRACT_NUM(0.038060), FRACT_NUM(0.040443), FRACT_NUM(0.042895), FRACT_NUM(0.045416), FRACT_NUM(0.048005), FRACT_NUM(0.050663), FRACT_NUM(0.053388), FRACT_NUM(0.056180),
	FRACT_NUM(0.059039), FRACT_NUM(0.061965), FRACT_NUM(0.064957), FRACT_NUM(0.068014), FRACT_NUM(0.071136), FRACT_NUM(0.074322), FRACT_NUM(0.077573), FRACT_NUM(0.080888),
	FRACT_NUM(0.084265), FRACT_NUM(0.087705), FRACT_NUM(0.091208), FRACT_NUM(0.094771), FRACT_NUM(0.098396), FRACT_NUM(0.102082), FRACT_NUM(0.105827), FRACT_NUM(0.109631),
	FRACT_NUM(0.113495), FRACT_NUM(0.117416), FRACT_NUM(0.121396), FRACT_NUM(0.125432), FRACT_NUM(0.129524), FRACT_NUM(0.133673), FRACT_NUM(0.137876), FRACT_NUM(0.142135),
	FRACT_NUM(0.146447), FRACT_NUM(0.150812), FRACT_NUM(0.155230), FRACT_NUM(0.159699), FRACT_NUM(0.164221), FRACT_NUM(0.168792), FRACT_NUM(0.173414), FRACT_NUM(0.178084),
	FRACT_NUM(0.182803), FRACT_NUM(0.187570), FRACT_NUM(0.192384), FRACT_NUM(0.197245), FRACT_NUM(0.202150), FRACT_NUM(0.207101), FRACT_NUM(0.212096), FRACT_NUM(0.217134),
	FRACT_NUM(0.222215), FRACT_NUM(0.227337), FRACT_NUM(0.232501), FRACT_NUM(0.237705), FRACT_NUM(0.242949), FRACT_NUM(0.248231), FRACT_NUM(0.253551), FRACT_NUM(0.258908),
	FRACT_NUM(0.264302), FRACT_NUM(0.269731), FRACT_NUM(0.275194), FRACT_NUM(0.280692), FRACT_NUM(0.286222), FRACT_NUM(0.291785), FRACT_NUM(0.297379), FRACT_NUM(0.303004),
	FRACT_NUM(0.308658), FRACT_NUM(0.314341), FRACT_NUM(0.320053), FRACT_NUM(0.325791), FRACT_NUM(0.331555), FRACT_NUM(0.337345), FRACT_NUM(0.343159), FRACT_NUM(0.348997),
	FRACT_NUM(0.354858), FRACT_NUM(0.360740), FRACT_NUM(0.366644), FRACT_NUM(0.372567), FRACT_NUM(0.378510), FRACT_NUM(0.384471), FRACT_NUM(0.390449), FRACT_NUM(0.396444),
	FRACT_NUM(0.402455), FRACT_NUM(0.408480), FRACT_NUM(0.414519), FRACT_NUM(0.420571), FRACT_NUM(0.426635), FRACT_NUM(0.432710), FRACT_NUM(0.438795), FRACT_NUM(0.444889),
	FRACT_NUM(0.450991), FRACT_NUM(0.457101), FRACT_NUM(0.463218), FRACT_NUM(0.469340), FRACT_NUM(0.475466), FRACT_NUM(0.481596), FRACT_NUM(0.487729), FRACT_NUM(0.493864)
};
