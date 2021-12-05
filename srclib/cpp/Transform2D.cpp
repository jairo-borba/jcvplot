//
// Created by Jairo Borba on 11/24/21.
//
#include "../include/jcvplot/Transform2D.h"
namespace jcvplot {
    void Transform2D::matrixMultiplication(
            double outMtx[2][2],
            double input1Mtx[2][2],
            double input2Mtx[2][2]
    ){
        for(auto i = 0; i < 2; ++i) {
            for (auto j = 0; j < 2; ++j) {
                for (auto k = 0; k < 2; ++k) {
                    outMtx[i][j] += input1Mtx[i][k] * input2Mtx[k][j];
                }
            }
        }
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