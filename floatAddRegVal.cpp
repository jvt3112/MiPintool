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

// The running count of instructions is kept here make it static to help the compiler optimize docount
static UINT64 icount = 0;
// This function is called before every instruction is executed

VOID docount() { icount++; }

VOID FloatValueRegMemPacked(PIN_REGISTER* reg1, ADDRINT addr, uint32_t size, bool checkSP){
    if(checkSP){
        FLT32 value;
        for (unsigned int i=0; i<MAX_FLOATS_PER_PIN_REG; i++){
            PIN_SafeCopy(&value, (void *)(addr + 4*i), 4);
            OutFile << "SP " << reg1->flt[i] << " " << value << std::endl;
       }
    }
    else{
        FLT64 value;
        for (unsigned int i=0; i<MAX_DOUBLES_PER_PIN_REG; i++){
            PIN_SafeCopy(&value, (void *)(addr + 8*i), 8);
            OutFile << "DP " << reg1->dbl[i] << " " << value << std::endl;
        }
    }
}
VOID FloatValueRegMemPackedType2(PIN_REGISTER* reg1, ADDRINT addr, uint32_t size, bool checkSP){
    if(checkSP){
        FLT32 value;
        for (unsigned int i=1; i<MAX_FLOATS_PER_PIN_REG; i=i+2){
            PIN_SafeCopy(&value, (void *)(addr + 4*i), 4);
            OutFile << "SP " << reg1->flt[i] << " " << value << std::endl;
       }
    }
    else{
        FLT64 value;
        for (unsigned int i=1; i<MAX_DOUBLES_PER_PIN_REG; i=i+2){
            PIN_SafeCopy(&value, (void *)(addr + 8*i), 8);
            OutFile << "DP " << reg1->dbl[i] << " " << value << std::endl;
        }
    }
    
}
VOID FloatValueRegMemPackedType3(PIN_REGISTER* reg1, ADDRINT addr, uint32_t size, bool checkSP){
    if(checkSP){
        FLT32 value1;
        FLT32 value2;
        for (unsigned int i=0; i<MAX_FLOATS_PER_PIN_REG; i=i+2){
            OutFile << "SP " << reg1->flt[i] << " " << reg1->flt[i+1] << std::endl;
       }
       for (unsigned int i=0; i<MAX_FLOATS_PER_PIN_REG; i=i+2){
            PIN_SafeCopy(&value1, (void *)(addr + 4*i), 4);
            PIN_SafeCopy(&value2, (void *)(addr + 4*(i+1)), 4);
            OutFile << "SP " << value1 << " " << value2 << std::endl;
       }
    }
    else{
        FLT64 value1;
        FLT64 value2;
        for (unsigned int i=0; i<MAX_DOUBLES_PER_PIN_REG; i=i+2){
            OutFile << "DP " << reg1->dbl[i] << " " << reg1->dbl[i+1] << std::endl;
       }
       for (unsigned int i=0; i<MAX_DOUBLES_PER_PIN_REG; i=i+2){
            PIN_SafeCopy(&value1, (void *)(addr + 8*i), 8);
            PIN_SafeCopy(&value2, (void *)(addr + 8*(i+1)), 8);
            OutFile << "DP " << value1 << " " << value2 << std::endl;
       }
    }
    
}

VOID FloatValue2RegPacked(PIN_REGISTER* reg1, PIN_REGISTER* reg2, bool checkSP){
    if(checkSP){
        for (unsigned int i=0; i<MAX_FLOATS_PER_PIN_REG; i++){
        OutFile <<  "SP " << reg1->flt[i] << " " << reg2->flt[i] << std::endl;
        }
    }
    else{
        for (unsigned int i=0; i < MAX_DOUBLES_PER_PIN_REG; i++){
        OutFile <<  "DP " << reg1->dbl[i] << " " << reg2->dbl[i] << std::endl;
        }
    }
}
VOID FloatValue2RegPackedType2(PIN_REGISTER* reg1, PIN_REGISTER* reg2, bool checkSP){
    if(checkSP){
        for (unsigned int i=1; i<MAX_FLOATS_PER_PIN_REG; i=i+2){
        OutFile <<  "SP " << reg1->flt[i] << " " << reg2->flt[i] << std::endl;
        }
    }
    else{
        for (unsigned int i=1; i < MAX_DOUBLES_PER_PIN_REG; i=i+2){
        OutFile <<  "DP " << reg1->dbl[i] << " " << reg2->dbl[i] << std::endl;
        }
    }
}

VOID FloatValue2RegPackedType3(PIN_REGISTER* reg1, PIN_REGISTER* reg2, bool checkSP){
    if(checkSP){
        for (unsigned int i=0; i<MAX_FLOATS_PER_PIN_REG; i=i+2){
        OutFile <<  "SP " << reg1->flt[i] << " " << reg1->flt[i+1] << std::endl;
        }
        for (unsigned int i=0; i<MAX_FLOATS_PER_PIN_REG; i=i+2){
        OutFile <<  "SP " << reg2->flt[i] << " " << reg2->flt[i+1] << std::endl;
        }
    }
    else{
        for (unsigned int i=0; i < MAX_DOUBLES_PER_PIN_REG; i=i+2){
        OutFile <<  "DP " << reg1->dbl[i] << " " << reg1->dbl[i+1] << std::endl;
        }
        for (unsigned int i=0; i < MAX_DOUBLES_PER_PIN_REG; i=i+2){
        OutFile <<  "DP " << reg2->dbl[i] << " " << reg2->dbl[i+1] << std::endl;
        }
    }
}

VOID FloatValueRegMem(PIN_REGISTER* reg1, ADDRINT addr, uint32_t size, bool checkSP){
    if(checkSP){
        FLT32 value;
        PIN_SafeCopy(&value, (void *)addr, size);
        OutFile << "SP " << reg1->flt[0] << " " << value << std::endl;
    }
    else{
        FLT64 value;
        PIN_SafeCopy(&value, (void *)addr, size);
        OutFile << "DP " << reg1->dbl[0] << " " << value << std::endl;
    }
    
}


VOID FloatValue2Reg(PIN_REGISTER* reg1, PIN_REGISTER* reg2, bool checkSP){
    if(checkSP){
        OutFile << "SP " << reg1->flt[0] << " " << reg2->flt[0] << std::endl;
    }
    else{
        OutFile << "DP " << reg1->dbl[0] << " " << reg2->dbl[0] << std::endl;
    }
}
VOID FloatValueMem(ADDRINT addr, uint32_t size, bool checkSP){
    if(checkSP){
        FLT32 value;
        PIN_SafeCopy(&value, (void *)addr, size);
        OutFile << "SP " << value << std::endl;
    }
    else{
        FLT64 value;
        PIN_SafeCopy(&value, (void *)addr, size);
        OutFile << "DP " << value << std::endl;
    }
    
}


// Pin calls this function every time a new instruction is encountered
VOID Instruction(INS ins, VOID *v)
{
    
    if(INS_Mnemonic(ins) == "FADD" 
        ){
        int opcount = INS_OperandCount(ins);
        if(opcount == 2){
            REG reg1 = INS_OperandReg(ins,0);
            REG reg2 = INS_OperandReg(ins,1);
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2Reg, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg2, IARG_BOOL, true, IARG_END);
        }
        if(opcount == 1){
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueMem,  IARG_MEMORYREAD_EA, IARG_MEMORYREAD_SIZE, IARG_BOOL, true, IARG_END);
        }
    }
    else if(INS_Mnemonic(ins) == "FIADD" 
        ){
        int opcount = INS_OperandCount(ins);
        if(opcount == 1){
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueMem,  IARG_MEMORYREAD_EA, IARG_MEMORYREAD_SIZE, IARG_BOOL, true, IARG_END);
        }
    }

    else if(INS_Mnemonic(ins) == "FADDP"
        ){
        int opcount = INS_OperandCount(ins);
        if(opcount == 2){
            REG reg1 = INS_OperandReg(ins,0);
            REG reg2 = INS_OperandReg(ins,1);
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2Reg, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg2, IARG_BOOL, true, IARG_END);
        }
    }
    else if(INS_Mnemonic(ins) == "ADDSS"
        ){
        // int opcount = INS_OperandCount(ins); All opcounts already found by research :p
        REG reg1 = INS_OperandReg(ins,0);
        if(INS_OperandIsMemory(ins,1))
        {
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueRegMem, IARG_REG_REFERENCE, reg1, IARG_MEMORYREAD_EA, IARG_MEMORYREAD_SIZE, IARG_BOOL, true, IARG_END);            
        }
        else
        {
            REG reg2 = INS_OperandReg(ins,1);
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2Reg, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg2, IARG_BOOL, true, IARG_END);
        }
    }
    else if(INS_Mnemonic(ins) == "ADDSD" 
        ){
        REG reg1 = INS_OperandReg(ins,0);
        if(INS_OperandIsMemory(ins,1))
        {
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueRegMem, IARG_REG_REFERENCE, reg1, IARG_MEMORYREAD_EA, IARG_MEMORYREAD_SIZE, IARG_BOOL, false, IARG_END);            
        }
        else
        {
            REG reg2 = INS_OperandReg(ins,1);
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2Reg, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg2, IARG_BOOL, false, IARG_END);
        }
    }
    else if( INS_Mnemonic(ins) == "ADDPS" 
        ){
        // int opcount = INS_OperandCount(ins); All opcounts already found by research :p
        REG reg1 = INS_OperandReg(ins,0);
        if(INS_OperandIsMemory(ins,1))
        {
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueRegMemPacked, IARG_REG_REFERENCE, reg1, IARG_MEMORYREAD_EA, IARG_MEMORYREAD_SIZE, IARG_BOOL, true, IARG_END);            
        }
        else
        {
            REG reg2 = INS_OperandReg(ins,1);
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2RegPacked, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg2, IARG_BOOL, true, IARG_END);
        }
    }
    else if( 
        INS_Mnemonic(ins) == "HADDPS"
        ){
        // int opcount = INS_OperandCount(ins); All opcounts already found by research :p
        REG reg1 = INS_OperandReg(ins,0);
        if(INS_OperandIsMemory(ins,1))
        {
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueRegMemPackedType3, IARG_REG_REFERENCE, reg1, IARG_MEMORYREAD_EA, IARG_MEMORYREAD_SIZE, IARG_BOOL, true, IARG_END);            
        }
        else
        {
            REG reg2 = INS_OperandReg(ins,1);
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2RegPackedType3, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg2, IARG_BOOL, true, IARG_END);
        }
    }
    else if( 
        INS_Mnemonic(ins) == "ADDSUBPS"
        ){
        // int opcount = INS_OperandCount(ins); All opcounts already found by research :p
        REG reg1 = INS_OperandReg(ins,0);
        if(INS_OperandIsMemory(ins,1))
        {
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueRegMemPackedType2, IARG_REG_REFERENCE, reg1, IARG_MEMORYREAD_EA, IARG_MEMORYREAD_SIZE, IARG_BOOL, true, IARG_END);            
        }
        else
        {
            REG reg2 = INS_OperandReg(ins,1);
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2RegPackedType2, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg2, IARG_BOOL, true, IARG_END);
        }
    }

    else if(INS_Mnemonic(ins) == "ADDPD"
        ){
        // int opcount = INS_OperandCount(ins); All opcounts already found by research :p
        REG reg1 = INS_OperandReg(ins,0);
        if(INS_OperandIsMemory(ins,1))
        {
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueRegMemPacked, IARG_REG_REFERENCE, reg1, IARG_MEMORYREAD_EA, IARG_MEMORYREAD_SIZE, IARG_BOOL, false, IARG_END);            
        }
        else
        {
            REG reg2 = INS_OperandReg(ins,1);
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2RegPacked, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg2, IARG_BOOL, false, IARG_END);
        }
    }
    else if(   
        INS_Mnemonic(ins) == "HADDPD"
        ){
        // int opcount = INS_OperandCount(ins); All opcounts already found by research :p
        REG reg1 = INS_OperandReg(ins,0);
        if(INS_OperandIsMemory(ins,1))
        {
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueRegMemPackedType3, IARG_REG_REFERENCE, reg1, IARG_MEMORYREAD_EA, IARG_MEMORYREAD_SIZE, IARG_BOOL, false, IARG_END);            
        }
        else
        {
            REG reg2 = INS_OperandReg(ins,1);
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2RegPackedType3, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg2, IARG_BOOL, false, IARG_END);
        }
    }
    else if(  
        INS_Mnemonic(ins) == "ADDSUBPD" 
        ){
        // int opcount = INS_OperandCount(ins); All opcounts already found by research :p
        REG reg1 = INS_OperandReg(ins,0);
        if(INS_OperandIsMemory(ins,1))
        {
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueRegMemPackedType2, IARG_REG_REFERENCE, reg1, IARG_MEMORYREAD_EA, IARG_MEMORYREAD_SIZE, IARG_BOOL, false, IARG_END);            
        }
        else
        {
            REG reg2 = INS_OperandReg(ins,1);
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2RegPackedType2, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg2, IARG_BOOL, false, IARG_END);
        }
    }

    else if(INS_Mnemonic(ins) == "VFMADD132SS" ||
        INS_Mnemonic(ins) == "VFNMADD132SS"
        ){
            REG reg1 = INS_OperandReg(ins,0);
            REG reg2 = INS_OperandReg(ins,1);
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2Reg, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg2, IARG_BOOL, true, IARG_END);       
    }
    else if(INS_Mnemonic(ins) == "VFMADD132SD" ||
        INS_Mnemonic(ins) == "VFNMADD132SD"
        ){
            REG reg1 = INS_OperandReg(ins,0);
            REG reg2 = INS_OperandReg(ins,1);
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2Reg, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg2, IARG_BOOL, false, IARG_END);       
    }
    else if(
        INS_Mnemonic(ins) == "VFMADD132PS" ||
        INS_Mnemonic(ins) == "VFMADDSUB132PS" ||
        INS_Mnemonic(ins) == "VFMSUBADD132PS" ||
        INS_Mnemonic(ins) == "VFNMADD132PS" 
        ){
            REG reg1 = INS_OperandReg(ins,0);
            REG reg2 = INS_OperandReg(ins,1);
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2RegPacked, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg2, IARG_BOOL, true, IARG_END);       
    }
    else if(INS_Mnemonic(ins) == "VFMADD132PD" ||
        INS_Mnemonic(ins) == "VFMADDSUB132PD" ||
        INS_Mnemonic(ins) == "VFMSUBADD132PD" ||  
        INS_Mnemonic(ins) == "VFNMADD132PD" 
        ){
            REG reg1 = INS_OperandReg(ins,0);
            REG reg2 = INS_OperandReg(ins,1);
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2RegPacked, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg2, IARG_BOOL, false, IARG_END);       
    }
    else if(INS_Mnemonic(ins) == "VFMADD213SS" ||
        INS_Mnemonic(ins) == "VFNMADD213SS"
        ){
            REG reg1 = INS_OperandReg(ins,0);
            if(INS_OperandIsMemory(ins,2))
            {
                INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueRegMem, IARG_REG_REFERENCE, reg1, IARG_MEMORYREAD_EA, IARG_MEMORYREAD_SIZE, IARG_BOOL, true, IARG_END);            
            }
            else
            {
                REG reg3 = INS_OperandReg(ins,2);
                INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2Reg, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg3, IARG_BOOL, true, IARG_END);
            }    
    }
    else if(INS_Mnemonic(ins) == "VFMADD213SD" ||
        INS_Mnemonic(ins) == "VFNMADD213SD" 
        ){
            REG reg1 = INS_OperandReg(ins,0);
            if(INS_OperandIsMemory(ins,2))
            {
                INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueRegMem, IARG_REG_REFERENCE, reg1, IARG_MEMORYREAD_EA, IARG_MEMORYREAD_SIZE, IARG_BOOL, false, IARG_END);            
            }
            else
            {
                REG reg3 = INS_OperandReg(ins,2);
                INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2Reg, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg3, IARG_BOOL, false, IARG_END);
            }    
    }
    else if(
        INS_Mnemonic(ins) == "VFMADD213PS" ||
        INS_Mnemonic(ins) == "VFMADDSUB213PS" ||
        INS_Mnemonic(ins) == "VFMSUBADD213PS" ||
        INS_Mnemonic(ins) == "VFNMADD213PS" 
        ){
            REG reg1 = INS_OperandReg(ins,0);
            if(INS_OperandIsMemory(ins,2))
            {
                INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueRegMemPacked, IARG_REG_REFERENCE, reg1, IARG_MEMORYREAD_EA, IARG_MEMORYREAD_SIZE, IARG_BOOL, true, IARG_END);            
            }
            else
            {
                REG reg3 = INS_OperandReg(ins,2);
                INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2RegPacked, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg3, IARG_BOOL, true, IARG_END);
            }    
    }
    else if(INS_Mnemonic(ins) == "VFMADD213PD"||
        INS_Mnemonic(ins) == "VFMADDSUB213PD" ||
        INS_Mnemonic(ins) == "VFMSUBADD213PD" ||  
        INS_Mnemonic(ins) == "VFNMADD213PD"  
        ){
            REG reg1 = INS_OperandReg(ins,0);
            if(INS_OperandIsMemory(ins,2))
            {
                INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueRegMemPacked, IARG_REG_REFERENCE, reg1, IARG_MEMORYREAD_EA, IARG_MEMORYREAD_SIZE, IARG_BOOL, false, IARG_END);            
            }
            else
            {
                REG reg3 = INS_OperandReg(ins,2);
                INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2RegPacked, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg3, IARG_BOOL, false, IARG_END);
            }    
    }
    else if(INS_Mnemonic(ins) == "VFMADD231SS" ||
        INS_Mnemonic(ins) == "VFNMADD231SS"
        ){
            REG reg1 = INS_OperandReg(ins,0);
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueRegMem, IARG_REG_REFERENCE, reg1, IARG_BOOL, true, IARG_END);  
    }
    else if(INS_Mnemonic(ins) == "VFMADD231SD" ||
        INS_Mnemonic(ins) == "VFNMADD231SD" 
        ){
            REG reg1 = INS_OperandReg(ins,0);
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueRegMem, IARG_REG_REFERENCE, reg1, IARG_BOOL, false, IARG_END);  
    }
    else if(INS_Mnemonic(ins) == "VFMADD231PS" ||
        INS_Mnemonic(ins) == "VFMADDSUB231PS" ||
        INS_Mnemonic(ins) == "VFMSUBADD231PS" ||
        INS_Mnemonic(ins) == "VFNMADD231PS"
        ){
            REG reg1 = INS_OperandReg(ins,0);
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueRegMemPacked, IARG_REG_REFERENCE, reg1, IARG_BOOL, true, IARG_END);  
    }
    else if(INS_Mnemonic(ins) == "VFMADD231PD" ||
        INS_Mnemonic(ins) == "VFMADDSUB231PD" ||
        INS_Mnemonic(ins) == "VFMSUBADD231PD" ||  
        INS_Mnemonic(ins) == "VFNMADD231PD"
        ){
            REG reg1 = INS_OperandReg(ins,0);
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueRegMemPacked, IARG_REG_REFERENCE, reg1, IARG_BOOL, false, IARG_END);  
    }
    else if(INS_Mnemonic(ins) == "V4FMADDSS" ||
        INS_Mnemonic(ins) == "V4FNMADDSS"
        ){
            REG reg1 = INS_OperandReg(ins,0);
            if(INS_OperandIsMemory(ins,1))
            {
                INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueRegMem, IARG_REG_REFERENCE, reg1, IARG_MEMORYREAD_EA, IARG_MEMORYREAD_SIZE, IARG_BOOL, true, IARG_END);            
            }
            else
            {
                REG reg2 = INS_OperandReg(ins,1);
                INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2Reg, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg2, IARG_BOOL, true, IARG_END);
            }
    }
    else if(INS_Mnemonic(ins) == "V4FMADDPS"||
        INS_Mnemonic(ins) == "V4FNMADDPS" 
        ){
            REG reg1 = INS_OperandReg(ins,0);
            if(INS_OperandIsMemory(ins,1))
            {
                INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValueRegMemPacked, IARG_REG_REFERENCE, reg1, IARG_MEMORYREAD_EA, IARG_MEMORYREAD_SIZE, IARG_BOOL, true, IARG_END);            
            }
            else
            {
                REG reg2 = INS_OperandReg(ins,1);
                INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)FloatValue2RegPacked, IARG_REG_REFERENCE, reg1, IARG_REG_REFERENCE, reg2, IARG_BOOL, true, IARG_END);
            }
    }
}

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "floatAddRegVal.out", "specify output file name");

// This function is called when the application exits
VOID Fini(INT32 code, VOID *v)
{
    // Write to a file since cout and cerr maybe closed by the application
    OutFile.setf(ios::showbase);
    // OutFile << "Count " << icount << endl;
    OutFile.close();
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
    cerr << "This tool counts the number of dynamic instructions executed" << endl;
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
