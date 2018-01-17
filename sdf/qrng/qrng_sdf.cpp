# include "netxpto.h"

# include "binary_source.h"
# include "clock_20171219.h"
# include "m_qam_mapper.h"
# include "discrete_to_continuous_time.h"
# include "pulse_shaper_20180111.h"
# include "single_photon_source_20171218.h"
# include "polarizer_20180113.h"
# include "polarization_beam_splitter_20180109.h"
# include "single_photon_detector_20180111.h"
# include "qrng_decision_circuit.h"
# include "sink.h"

int main(){

	/*Input Parameters*/

	double RateOfPhotons{ 1e6 };
	int NumberOfSamplesPerSymbol{ 16 };
	vector<t_iqValues> iqAmplitudeValues = { { 0.0,0.0 },{ -45.0,0.0 },{ 90.0,0.0 },{ 45.0,0.0 } };

	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################
	
	Binary S1{ "S1.sgn" };

	TimeContinuousAmplitudeContinuousReal S2{ "S2.sgn" };

	TimeDiscreteAmplitudeDiscreteReal S3{ "S3.sgn" };

	TimeDiscreteAmplitudeDiscreteReal S4{ "S4.sgn" };

	TimeContinuousAmplitudeDiscreteReal S5{ "S5.sgn" };

	TimeContinuousAmplitudeDiscreteReal S6{ "S6.sgn" };

	PhotonStreamXY S7{ "S7.sgn" };

	PhotonStreamXY S8{ "S8.sgn" };

	PhotonStreamXYMP S9{ "S9.sgn" };

	TimeContinuousAmplitudeDiscreteReal S10{ "S10.sgn" };

	TimeContinuousAmplitudeDiscreteReal S11{ "S11.sgn" };

	Binary S12{ "S12.sgn" };

	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################


	BinarySource B1{ vector<Signal*> {}, vector<Signal*> { &S1 } };
	B1.setMode(DeterministicCyclic);
	B1.setBitPeriod(1/(2*RateOfPhotons));
	B1.setBitStream("11");
	//B1.setNumberOfBits(10e6);

	Clock B2{ vector<Signal*>{}, vector<Signal*>{&S2} };
	B2.setClockPeriod(1 / RateOfPhotons);
	B2.setSamplingPeriod((1 / RateOfPhotons) / NumberOfSamplesPerSymbol);
	B2.setClockPhase(3 * PI / 2);

	MQamMapper B3{ vector<Signal*>{&S1}, vector<Signal*>{&S3, &S4} };
	B3.setIqAmplitudes(iqAmplitudeValues);

	Sink B4{ vector<Signal*>{&S4}, vector<Signal*>{} };

	DiscreteToContinuousTime B5{ vector<Signal*>{&S3}, vector<Signal*>{&S5} };
	B5.setNumberOfSamplesPerSymbol(NumberOfSamplesPerSymbol);

	PulseShaper B6{ vector<Signal*>{&S5}, vector<Signal*>{&S6} };
	B6.setFilterType(Square);

	SinglePhotonSource B7{ vector<Signal*>{&S2},vector<Signal*>{&S7} };

	Polarizer B8{ vector<Signal*>{&S7, &S6}, vector<Signal*>{&S8} };

	PolarizationBeamSplitter B9{ vector<Signal*>{&S8}, vector<Signal*>{&S9} };

	SinglePhotonDetector B10{ vector<Signal*>{&S9}, vector<Signal*>{&S10} };
	B10.setPath(0);

	SinglePhotonDetector B11{ vector<Signal*>{&S9}, vector<Signal*>{&S11} };
	B11.setPath(1);

	QRNG_DecisionCircuit B12{ vector<Signal*>{&S10,&S11}, vector<Signal*>{&S12} };

	Sink B13{ vector<Signal*>{&S12}, vector<Signal*>{} };
	B13.setNumberOfSamples((long int) 10000);
	B13.setDisplayNumberOfSamples(true);

	
	
	// #####################################################################################################
	// ########################### System Declaration and Inicialization ###################################
	// #####################################################################################################

	System MainSystem{ vector<Block*> { &B1, &B2, &B3, &B4, &B5, &B6, &B7, &B8, &B9,&B10, &B11, &B12, &B13 } };

	// #####################################################################################################
	// #################################### System Run #####################################################
	// #####################################################################################################
	
	MainSystem.run();

	return 0;

}