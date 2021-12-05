//
// Created by Jairo Borba on 12/1/21.
//
#ifndef JCVPLOT_TRANSFORM3D_H
#define JCVPLOT_TRANSFORM3D_H
namespace jcvplot {
    class Transform3D {
    public:
        static const int DIMS = 3;
        static void matrixMultiplication(
                double outMtx[DIMS][DIMS],
                double input1Mtx[DIMS][DIMS],
                double input2Mtx[DIMS][DIMS]
        );
        static void yaw(double outMtx[DIMS][DIMS],
                        double inputMtx[DIMS][DIMS],
                        double angleX,
                        double angleY);
        static void pitch(double outMtx[DIMS][DIMS],
                        double inputMtx[DIMS][DIMS],
                          double angleX, double angleZ);
        static void roll(double outMtx[DIMS][DIMS],
                          double inputMtx[DIMS][DIMS],
                         double angleY, double angleZ);
        static void bypass(double outMtx[DIMS][DIMS],
                         double inputMtx[DIMS][DIMS],
                         double angleY, double angleZ);
        static void transform(
                const double transformMtx[DIMS][DIMS],
                const double preOffsetVector[DIMS],
                const double postOffsetVector[DIMS],
                const double inputVector[DIMS],
                double outputVector[DIMS]
        );
    };
}
#endif //JCVPLOT_TRANSFORM3D_H
