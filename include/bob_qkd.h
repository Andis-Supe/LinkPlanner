#ifndef BOB_QKD_H_
#define BOB_QKD_H

#include "netxpto_20180118.h"
#include "binary_mapper_20180205.h"
#include "discrete_to_continuous_time_20180118.h"
#include "pulse_shaper_20180111.h"
#include "super_block_interface_20180118.h"
#include "fork_20180112.h"
#include "detection_decision_circuit_20180206.h"
#include "sink.h"


class BobQKD : public SuperBlock {

	// #####################################################################################################
	// ################## Internal Signals Declaration and Inicialization ##################################
	// #####################################################################################################
	TimeDiscreteAmplitudeDiscreteReal Bob_1{ "Bob_1.sgn" };
	TimeContinuousAmplitudeDiscreteReal Bob_2{ "Bob_2.sgn" };
	TimeContinuousAmplitudeDiscreteReal Bob_3{ "Bob_3.sgn" };
	Binary Bob_4{ "Bob_4.sgn" };
	Binary Bob_5{ "Bob_5.sgn" };
	Binary Bob_6{ "Bob_6.sgn" };
	TimeDiscreteAmplitudeDiscreteReal Bob_7{ "Bob_7.sgn" };
	TimeDiscreteAmplitudeDiscreteReal Bob_11{ "Bob_11.sgn" };
	TimeContinuousAmplitudeDiscreteReal Bob_8{ "Bob_8.sgn" };
	TimeContinuousAmplitudeDiscreteReal S4{ "Bob_8_out.sgn" };
	
	TimeContinuousAmplitudeDiscreteReal CLKB_1{ "CLKB_1.sgn" };
	TimeContinuousAmplitudeDiscreteReal CLKB_2{ "CLKB_2.sgn" };
	TimeContinuousAmplitudeDiscreteReal CLKB_out1{ "CLKB_out1.sgn" };
	TimeContinuousAmplitudeDiscreteReal CLKB_out2{ "CLKB_out2.sgn" };

	
	

	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################
	BinaryMapper BB0;
	DiscreteToContinuousTime BB1;
	PulseShaper BB2;

	PulseShaper BB3;
	Fork BB4;

	SuperBlockInterface BB9;

	DetectionDecisionCircuit BB10;
	Sink BBSink;

public:
	/* input parameters*/


	BobQKD(vector <Signal*> &inputSignals, vector <Signal*> &outputSignals);

	void setNumberOfSamplesPerSymbol(int n) { BB1.setNumberOfSamplesPerSymbol(n); };
	int const getNumberOfSamplesPerSymbol(void) { return BB1.getNumberOfSamplesPerSymbol(); };

	void setSeeBeginningOfImpulseResponse(bool sBeginningOfImpulseResponse) { BB2.setSeeBeginningOfImpulseResponse(sBeginningOfImpulseResponse); };
	double const getSeeBeginningOfImpulseResponse(void) { return BB2.getSeeBeginningOfImpulseResponse(); };

	void setPulseShaperFilter(PulseShaperFilter fType) { BB2.setFilterType(fType); BB3.setFilterType(fType); };

	void setPulseWidth(double tWidth) { BB3.setPulseWidth(tWidth); };
	double getPulseWidth() { return BB3.getPulseWidth(); };

	void setPulseDelay(double pDelay) { BB3.setPulseDelay(pDelay); };
	double getPulseDelay() { return BB3.getPulseDelay(); };

};

#endif
