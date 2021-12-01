//
// Created by Jairo Borba on 11/25/21.
//

#ifndef JCVPLOT_AXISANGLE_H
#define JCVPLOT_AXISANGLE_H

namespace jcvplot {
    class AxisAngle {
    private:
        double xAxisAngle;
        double yAxisAngle;
        double zAxisAngle;
    public:
        AxisAngle(
                double a_xAxisAngleRad = 0.0,
                double a_yAxisAngleRad = 0.0,
                double a_zAxisAngleRad = 0.0):
                xAxisAngle(a_xAxisAngleRad),
                yAxisAngle(a_yAxisAngleRad),
                zAxisAngle(a_zAxisAngleRad){
        }
        double x_rad() const{return xAxisAngle;}
        double y_rad() const{return yAxisAngle;}
        double z_rad() const{return zAxisAngle;}
        static double rad2Degree(double rad){
            static const auto pi = acos(-1);
            static const auto angleCoefficient = pi/180.0;
            auto degree = rad / angleCoefficient;

            return degree;
        }
        static double degree2Rad(double degree){
            static const auto pi = acos(-1);
            static const auto angleCoefficient = pi/180.0;
            auto rad = degree * angleCoefficient;

            return rad;
        }
    };
}

#endif //JCVPLOT_AXISANGLE_H
