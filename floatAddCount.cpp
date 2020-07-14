/*
 * Copyright 2002-2019 Intel Corporation.
 * 
 * This software is provided to you as Sample Source Code as defined in the accompanying
 * End User License Agreement for the Intel(R) Software Development Products ("Agreement")
 * section 1.L.
 * 
 * This software and the related documents are provided as is, with no express or implied
 * warranties, other than those that are expressly stated in the License.
 */

#include <iostream>
#include <fstream>
#include "pin.H"
using std::cerr;
using std::ofstream;
using std::ios;
using std::string;
using std::endl;

ofstream OutFile;

// The running count of instructions is kept here
// make it static to help the compiler optimize docount
static UINT64 icount = 0;

// This function is called before every instruction is executed
VOID docount() { icount++; }
    
// Pin calls this function every time a new instruction is encountered
VOID Instruction(INS ins, VOID *v)
{
    const char *all_float_add_ins[58] = { "ADDPD" , "ADDPS", "ADDSD", "ADDSS", "ADDSUBPD", "ADDSUBPS", "FADD", "FADDP", "FIADD", "HADDPD", "HADDPS", "VFMADD132PD", "VFMADD132PS", "VFMADD132SD", "VFMADD132SS", "VFMADD213PD", "VFMADD213PS", "VFMADD213SD", "VFMADD213SS", "VFMADD231PD", "VFMADD231PS", "VFMADD231SD", "VFMADD231SS", "VFMADDSUB132PD", "VFMADDSUB132PS", "VFMADDSUB213PD" , "VFMADDSUB213PS" , "VFMADDSUB231PD" , "VFMADDSUB231PS", "VFMSUBADD132PD" , "VFMSUBADD132PS", "VFMSUBADD213PD", "VFMSUBADD213PS", "VFMSUBADD231PD" ,"VFMSUBADD231PS", "VFNMADD132PD", "VFNMADD132PS", "VFNMADD132SD", "VFNMADD132SS", "VFNMADD213PD", "VFNMADD213SD", "VFNMADD213SS", "VFNMADD231PD", "VFNMADD231PS", "VFNMADD231SD", "VFNMADD231SS", "V4FMADDPS", "V4FMADDSS", "V4FNMADDPS", "V4FNMADDSS", "VRNDSCALEPD", "VRNDSCALEPS", "VRNDSCALESD", "VRNDSCALESS", "V4FMADDPS", "V4FMADDSS", "V4FNMADDPS", "V4FNMADDSS"};
    
    for(int i=0; i<58; i++){
	    if(all_float_add_ins[i]==INS_Mnemonic(ins)){
	    	// Insert a call to docount before every instruction, no arguments are passed
	    	INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)docount, IARG_END);
    	}
    }
    
    
}

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "floatAddCount.out", "specify output file name");

// This function is called when the application exits
VOID Fini(INT32 code, VOID *v)
{
    // Write to a file since cout and cerr maybe closed by the application
    OutFile.setf(ios::showbase);
    OutFile << "Count " << icount << endl;
    OutFile.close();
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
    cerr << "This tool counts the number of float point addition instructions executed" << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */
/*   argc, argv are the entire command line: pin -t <toolname> -- ...    */
/* ===================================================================== */

int main(int argc, char * argv[])
{
    // Initialize pin
    if (PIN_Init(argc, argv)) return Usage();

    OutFile.open(KnobOutputFile.Value().c_str());

    // Register Instruction to be called to instrument instructions
    INS_AddInstrumentFunction(Instruction, 0);

    // Register Fini to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);
    
    // Start the program, never returns
    PIN_StartProgram();
    
    return 0;
}