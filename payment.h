#pragma once

#include <iostream>

#include "tariffs.h"

struct Date {
    int month;
    int year;
};

class Payment {
public:
    Payment();
    ~Payment() = default;

    void ProceedInput();
    double CalculateCostWater();
    double CalculateCostGas();
    double CalculateCostLight();
    double CalculateCostRent();
    double CalculateCostGarbage();
    
    int IsInt(int number);
    void SetData();
    void SetMeters();
    const Date& GetDate() const;
    const std::pair<int, int> GetWaterMeters() const;
    const std::pair<int, int> GetGasMeters() const;
    const std::pair<int, int> GetLightMeters() const;
    
private:
    Date date_;
    int water_meter_ = 0;
    int water_meter_prev_ = 0;
    int gas_meter_ = 0;
    int gas_meter_prev_ = 0;
    int light_meter_ = 0;
    int light_meter_prev_ = 0;
};
