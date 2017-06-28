// Trasmiss�o de um sinal bin�rio usando apenas 1 base.

# include "netxpto.h"

# include "m_qam_transmitter.h"
# include "i_homodyne_receiver.h"
# include "sink.h"
# include "bit_error_rate.h"
# include "local_oscillator.h"
# include "balanced_beam_splitter.h"
# include "photodiode.h"
# include "ti_amplifier.h"
# include "sampler.h"
# include "optical_hybrid.h"
# include "testblock.h"
# include "sampler.h"
# include "bit_decider.h"


int main()
{
	
	// #####################################################################################################
	// #################################### System Input Parameters ########################################
	// #####################################################################################################



	int numberOfBitsGenerated(50);

	int samplesPerSymbol(64);
	//double bitPeriod = 1.0/5e9;
	double bitPeriod = 1.0E-9;

	// powerUnit = PLANCK_CONSTANT * SPEED_OF_LIGHT / (bitPeriod*wavelength)
	// We will assume: wavelength = 1.550E-6
	//double powerUnit = 6.4078e-13;
	double wavelength = 1.55e-6;
	double powerUnit = PLANCK_CONSTANT*SPEED_OF_LIGHT/(bitPeriod/samplesPerSymbol*wavelength);
	
	double localOscillatorPower1 = powerUnit * 500 ;
	//double localOscillatorPower_dBm1 = -91.933;
	
	double localOscillatorPower2 = powerUnit * 500;
	//double localOscillatorPower_dBm2 = 10;

	double localOscillatorPhase = 0;
	array<t_complex, 4> transferMatrix = { { 1 / sqrt(2), 1 / sqrt(2), 1 / sqrt(2), -1 / sqrt(2) } };
	double responsivity = 1;
	double amplification = 1e6;
	double electricalNoiseAmplitude = 0;// 0.0022*0.0022;
	int bufferLength = 512;
	bool shotNoise(true);
	vector<t_iqValues> iqAmplitudeValues = { { -1, 0 },{ 1, 0 } };

	double SNR = 0;





	// #########################################################################
	// ################ Signals Declaration and Inicialization #################
	// #########################################################################




	// %%%%%%%%%%%%%%%% ALICE SIGNAL GENERATION %%%%%%%%%%%%%%%%

	// Gera��o dos sinais bin�rios
	Binary S0("S0.sgn");
	S0.setBufferLength(bufferLength);

	// Sinal �ptico 
	OpticalSignal S1("S1.sgn");
	S1.setBufferLength(bufferLength);
	
	


	// %%%%%%%%%%%%%%%%   BOB SIGNAL DETECTION   %%%%%%%%%%%%%%%%

	OpticalSignal S2("S2.sgn");
	S2.setBufferLength(bufferLength);

	OpticalSignal S3("S3.sgn");
	S3.setBufferLength(bufferLength);

	OpticalSignal S4("S4.sgn");
	S4.setBufferLength(bufferLength);

	OpticalSignal S5("S5.sgn");
	S3.setBufferLength(bufferLength);

	OpticalSignal S6("S6.sgn");
	S6.setBufferLength(bufferLength);

	TimeContinuousAmplitudeContinuousReal S7("S7.sgn");
	S7.setBufferLength(bufferLength);

	TimeDiscreteAmplitudeContinuousReal S8("S8.sgn");
	S8.setBufferLength(bufferLength);

	TimeDiscreteAmplitudeContinuousReal S9("S9.sgn");
	S9.setBufferLength(bufferLength);

	TimeDiscreteAmplitudeContinuousReal S10("S10.sgn");
	S10.setBufferLength(bufferLength);

	// #########################################################################
	// ################# Blocks Declaration and Inicialization #################
	// #########################################################################

	// BEGIN ALICE

	MQamTransmitter B1{ vector<Signal*> {}, vector<Signal*> {&S1, &S0} };
	B1.setNumberOfBits(numberOfBitsGenerated);
	B1.setOutputOpticalPower(localOscillatorPower1);
	//B1.setOutputOpticalPower_dBm(localOscillatorPower_dBm1);
	
	B1.setMode(PseudoRandom);
	//B1.setMode(Random);
	
	B1.setBitPeriod(bitPeriod);
	B1.setIqAmplitudes(iqAmplitudeValues);
	B1.setPulseShaperFilter(Gaussian);

	B1.setNumberOfSamplesPerSymbol(samplesPerSymbol);
	B1.setSaveInternalSignals(true);
	B1.setSeeBeginningOfImpulseResponse(true);

	// END ALICE




	// BEGIN BOB.

	LocalOscillator B13{ vector<Signal*> {}, vector<Signal*> {&S2} };
	B13.setOpticalPower(localOscillatorPower2);
	B13.setPhase(localOscillatorPhase);
	B13.setSamplingPeriod(bitPeriod / samplesPerSymbol);
	B13.setSymbolPeriod(bitPeriod);
	B13.setSignaltoNoiseRatio(SNR);

	OpticalHybrid B14{ vector<Signal*> {&S1, &S2},
					   vector<Signal*> {&S3, &S4, &S5, &S6} };

	Photodiode B15{ vector<Signal*> { &S3, &S4 }, vector<Signal*> {&S7} };
	B15.useNoise(shotNoise);
	B15.setResponsivity(responsivity);

	Photodiode B16{ vector<Signal*> { &S5, &S6 }, vector<Signal*> {&S8} };
	B16.useNoise(shotNoise);
	B16.setResponsivity(responsivity);

	Sampler B17{ vector<Signal*> { &S7 }, vector<Signal*> { &S9 } };
	
	Sampler B18{ vector<Signal*> { &S8 }, vector<Signal*> { &S10 } };

	Sink B19{ vector<Signal*> {&S9}, vector<Signal*> {} };
	B19.setNumberOfSamples(samplesPerSymbol*numberOfBitsGenerated);
	B19.setDisplayNumberOfSamples(true);

	Sink B20{ vector<Signal*> {&S10}, vector<Signal*> {} };
	B20.setNumberOfSamples(samplesPerSymbol*numberOfBitsGenerated);
	B20.setDisplayNumberOfSamples(true);
	
	// END BOB



	Sink B21{ vector<Signal*> {&S0}, vector<Signal*> {} };
	B21.setNumberOfSamples(samplesPerSymbol*numberOfBitsGenerated);
	B21.setDisplayNumberOfSamples(true);


	// #####################################################################################################
	// ########################### System Declaration and Inicialization ###################################
	// #####################################################################################################


	System MainSystem{ vector<Block*> {&B1, &B13, &B14, &B15, &B16, &B17, &B18,
					   &B19, &B20, &B21} };


	// #####################################################################################################
	// #################################### System Run #####################################################
	// #####################################################################################################

	MainSystem.run();

    return 0;
}