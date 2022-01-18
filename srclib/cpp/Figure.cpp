//
// Created by Jairo Borba on 10/31/21.
//
#include "../include/jcvplot/Figure.h"
namespace jcvplot {
    Figure::Figure():
            m_on(true),
            m_id("Figure","no-Description"),
            m_color(Figure::Color_t(0,0,0)),
            m_scale(1.0f),
            m_offset(0,0,0),
            m_yawAngle(){
    }
    Figure& Figure::setID(const ID &id){
        m_id = id;
        return *this;
    }
    Figure& Figure::off(){
        m_on = false;
        return *this;
    }
    Figure& Figure::on(){
        m_on = true;
        return *this;
    }
    bool Figure::isOn()const{
        return m_on;
    }
    Figure& Figure::addFigure(std::shared_ptr<Figure> fig, int seq_no){
        this->m_figures.insert(FigureContainerPair_t(seq_no,fig));
        return *this;
    }
    Figure& Figure::addDynamicFigure(std::shared_ptr<Figure> fig, int seq_no){
        this->m_dynamicFigures.insert(FigureContainerPair_t(seq_no,fig));
        return *this;
    }
    const Figure::FigureContainer_t& Figure::figures()const{
        return m_figures;
    }
    Figure::FigureContainer_t& Figure::figures(){
        return m_figures;
    }
    const Figure::FigureContainer_t& Figure::dynamicFigures()const{
        return m_dynamicFigures;
    }
    Figure::FigureContainer_t& Figure::dynamicFigures(){
        return m_dynamicFigures;
    }
    Figure& Figure::setColor(const Figure::Color_t &color){
        m_color = color;
        return *this;
    }
    const Figure::Color_t & Figure::color() const{
        return m_color;
    }
    cv::Scalar Figure::scalarColor() const{
        return cv::Scalar(m_color.x,m_color.y,m_color.z);
    }
    Figure& Figure::setScale(float scale){
        m_scale = scale;
        return *this;
    }
    float Figure::scale() const{
        return m_scale;
    }
    Figure& Figure::setOffset(const Figure::Offset_t &offset){
        m_offset = offset;
        return *this;
    }
    const Figure::Offset_t &Figure::offset() const{
        return m_offset;
    }
    const std::shared_ptr<Tensor> &Figure::tensor() const {
        return m_tensor;
    }
    void Figure::setTensor(const std::shared_ptr<Tensor> &mTensor) {
        m_tensor = mTensor;
    }
    const AxisAngle& Figure::yawAngle()const{
        return m_yawAngle;
    }
    Figure &Figure::setYawAngle(const AxisAngle& yawAngle){
        m_yawAngle = yawAngle;
        return *this;
    }
    const AxisAngle& Figure::rollAngle()const{
        return m_rollAngle;
    }
    Figure &Figure::setRollAngle(const AxisAngle& rollAngle){
        m_rollAngle = rollAngle;
        return *this;
    }
    const AxisAngle& Figure::pitchAngle()const{
        return m_pitchAngle;
    }
    Figure &Figure::setPitchAngle(const AxisAngle& pitchAngle){
        m_pitchAngle = pitchAngle;
        return *this;
    }
}
