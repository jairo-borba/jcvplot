//
// Created by Jairo Borba on 11/24/21.
//

#ifndef JCVPLOT_TRANSFORM2D_H
#define JCVPLOT_TRANSFORM2D_H
#include <opencv2/opencv.hpp>
namespace jcvplot {
    class Transform2D {
    public:
        static void transform(
                const double transformMtx[2][2],
                const double preOffsetVector[2],
                const double postOffsetVector[2],
                const double inputVector[2],
                double outputVector[2]
        );

        static void matrixMultiplication(
                double outMtx[2][2],
                double input1Mtx[2][2],
                double input2Mtx[2][2]
                );
    };
}
#endif //JCVPLOT_TRANSFORM2D_H
