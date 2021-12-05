//
// Created by Jairo Borba on 12/1/21.
//
#include "Transform3D.h"
#include <cmath>
namespace jcvplot {
    void Transform3D::matrixMultiplication(
            double outMtx[DIMS][DIMS],
            double input1Mtx[DIMS][DIMS],
            double input2Mtx[DIMS][DIMS]
    ){
        for(auto i = 0; i < DIMS; ++i) {
            for (auto j = 0; j < DIMS; ++j) {
                for (auto k = 0; k < DIMS; ++k) {
                    outMtx[i][j] += input1Mtx[i][k] * input2Mtx[k][j];
                }
            }
        }
    }
    void Transform3D::yaw(double outMtx[DIMS][DIMS],
             double inputMtx[DIMS][DIMS],
             double angleX,
             double angleY){
        double rotation[DIMS][DIMS]{
                cos(angleX),-sin(angleY),0.0,
                sin(angleX), cos(angleY),0.0,
                0.0,0.0,1.0
        };
        matrixMultiplication(outMtx,rotation,inputMtx);
    }
    void Transform3D::pitch(
            double outMtx[DIMS][DIMS],
            double inputMtx[DIMS][DIMS],
            double angleX, double angleZ){
        double rotation[DIMS][DIMS]{
                cos(angleX),0.0,sin(angleZ),
                0.0,1.0,0.0,
                -sin(angleX), 0.0, cos(angleZ)
        };
        matrixMultiplication(outMtx,rotation,inputMtx);
    }
    void Transform3D::bypass(
            double outMtx[DIMS][DIMS],
            double inputMtx[DIMS][DIMS],
            double angleX, double angleZ){
        double rotation[DIMS][DIMS]{
                1.0,0.0,1.0,
                0.0,1.0,0.0,
                0.0,0.0,1.0
        };
        matrixMultiplication(outMtx,rotation,inputMtx);
    }
    void Transform3D::roll(double outMtx[DIMS][DIMS],
                          double inputMtx[DIMS][DIMS],
                          double angleY, double angleZ){
        double rotation[DIMS][DIMS]{
            1.0,0.0,0.0,
            0.0,cos(angleY),-sin(angleZ),
            0.0,sin(angleY), cos(angleZ)
        };
        matrixMultiplication(outMtx,rotation,inputMtx);
    }
    void Transform3D::transform(
            const double transformMtx[DIMS][DIMS],
            const double preOffsetVector[DIMS],
            const double postOffsetVector[DIMS],
            const double inputVector[DIMS],
            double outputVector[DIMS]
    ){
        double vector[DIMS]{
                inputVector[0]+preOffsetVector[0],
                inputVector[1]+preOffsetVector[1],
                inputVector[2]+preOffsetVector[2]};
        outputVector[0] =
                (transformMtx[0][0]*vector[0]) +
                (transformMtx[0][1]*vector[1]) +
                (transformMtx[0][2]*vector[2]) +
                postOffsetVector[0];
        outputVector[1] =
                (transformMtx[1][0]*vector[0]) +
                (transformMtx[1][1]*vector[1]) +
                (transformMtx[1][2]*vector[2]) +
                postOffsetVector[1];
        outputVector[2] =
                (transformMtx[2][0]*vector[0]) +
                (transformMtx[2][1]*vector[1]) +
                (transformMtx[2][2]*vector[2]) +
                postOffsetVector[2];
    }
}