#pragma once
#include <vector>
#include <stdexcept>
#include "nameable.h"
#include "helpers.h"
#include "logger.h"

class gate:virtual public nameable{
protected:
    friend class elem_file_saver;
    size_t width;
    std::vector<bool> values;

    logger& lg;

    void log(const std::string &msg)const{
        lg.log(this->get_name()+"("+std::to_string(get_id())+")", msg);
    }
public:
    gate(const std::string &name, const size_t &width=1, const size_t &parent_id=0)
        :nameable(name, parent_id),
        lg(logger::get_instance())
    {
        set_width(width);
    }
    virtual ~gate(){}

    virtual void set_width(const size_t &width){
        this->width = width;
        values.resize(width);
    }
    virtual const size_t& get_width()const{
        return width;
    }
    virtual bool get_value(const size_t &place)const{
        return values.at(place);
    }
    virtual const std::vector<bool>& get_values()const{
        return values;
    }

    virtual void set_values(const std::vector<bool> &values){
        if(values.size() != this->width){
            auto mes = "attempt to assign value of width "+std::to_string(values.size())+
                " to a gate "+get_name()+" with width "+std::to_string(width);
            throw std::runtime_error(mes);
        }
        this->values = values;
    }

    friend bool operator==(const gate &lhs, const gate &rhs){
        const nameable& lhs_n(lhs);
        const nameable& rhs_n(rhs);
        return lhs_n == rhs_n &&
            lhs.width == rhs.width;
    }
    friend bool operator!=(const gate &lhs, const gate &rhs){
        return !(lhs == rhs);
    }
};