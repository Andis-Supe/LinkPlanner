# ifndef PROGRAM_INCLUDE_DSP_H_
# define PROGRAM_INCLUDE_DSP_H_

# include "netxpto_20180118.h"

# include "real2complex.h"
# include "cpe.h"


// this is a test block for the purpose of beta testing new code
// current code: Building Homodyne superblock.
class DSP : public SuperBlock {

	// #####################################################################################################
	// ################## Internal Signals Declaration and Inicialization ##################################
	// #####################################################################################################


	BandpassSignal DSP01{ "DSP01.sgn" };  // real to complex
	BandpassSignal DSP02{ "DSP02.sgn" };  // cpe
	

 // #####################################################################################################
 // ########################### Blocks Declaration and Inicialization ###################################
 // #####################################################################################################

	Real2Complex B01;

	CPE B02;

	/* State Variables */

	/* Input Parameters */
	double samplingPeriod{ 0.0 };

public:

	/* Methods */

	DSP(vector<Signal *> &inputSignal, vector<Signal *> &outputSignal);

	/* Set Methods */
	
	void setCPEnTaps(int nTaps) { B02.setnTaps(nTaps); }
	void setCPETestPhase(int TestPhase) { B02.setTestPhase(TestPhase); }
	void setCPESamplingPeriod(double sPeriod) { B02.setSamplingPeriod(sPeriod); }
	void setCPEmethodType(int mType) { B02.setmethodType(mType); }

	void setSamplingPeriod(double sPeriod) { B02.setSamplingPeriod(sPeriod); };
	
};

#endif