////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     EMLL.i (interfaces)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

%module "EMLL"
#if defined(SWIGJAVASCRIPT)
%{
#include <node.h>
#include <v8.h>
#include <nan.h>
%}
#endif

%{
#include <vector>
%}

#ifndef SWIGXML
//%include typemaps.i
%include "std_string.i"
%include "std_vector.i"
%template(DoubleVector) std::vector<double>;
%template(DoubleVectorVector) std::vector<std::vector<double>>;
#endif

// ELL APIs 
%include "lossFunctions.i"
%include "model.i"

#if defined(SWIGJAVASCRIPT)
// Interface for NaN callbacks
%include callback.i

// Interface ELL Load Model Async
%include loadModelAsync.i
#endif


