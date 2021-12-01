//
// Created by Jairo Borba on 11/24/21.
//
#include "Transform2D.h"
namespace jcvplot {
    void Transform2D::matrixMultiplication(
            double outMtx[2][2],
            double input1Mtx[2][2],
            double input2Mtx[2][2]){
        outMtx[0][0] = input1Mtx[0][0] * input2Mtx[0][0] + input1Mtx[0][1] * input2Mtx[1][0];
        outMtx[0][1] = input1Mtx[0][0] * input2Mtx[0][1] + input1Mtx[0][1] * input2Mtx[1][1];
        outMtx[1][0] = input1Mtx[1][0] * input2Mtx[0][0] + input1Mtx[1][1] * input2Mtx[1][0];
        outMtx[1][1] = input1Mtx[1][0] * input2Mtx[0][1] + input1Mtx[1][1] * input2Mtx[1][1];
    }
        void Transform2D::transform(
                const double transformMtx[2][2],
                const double preOffsetVector[2],
                const double postOffsetVector[2],
                const double inputVector[2],
                double outputVector[2]
                ){
            double vector[2]{
                inputVector[0]+preOffsetVector[0],
                inputVector[1]+preOffsetVector[1]};
            outputVector[0] =
                    (transformMtx[0][0]*vector[0]) +
                    (transformMtx[0][1]*vector[1]) +
                    postOffsetVector[0];
            outputVector[1] =
                    (transformMtx[1][0]*vector[0]) +
                    (transformMtx[1][1]*vector[1]) +
                    postOffsetVector[1];
        }
}