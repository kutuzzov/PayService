#include "common.h"

#include <string>

using namespace std::string_view_literals;

void Print(Payment& date) {
    std::cout << std::endl;
    switch (date.GetDate().month) {
        case MONTH::JAN:
            std::cout << "январь"sv;
            break;
        case MONTH::FEB:
            std::cout << "февраль"sv;
            break;
        case MONTH::MAR:
            std::cout << "март"sv;
            break;
        case MONTH::APR:
            std::cout << "апрель"sv;
            break;
        case MONTH::MAY:
            std::cout << "май"sv;
            break;
        case MONTH::JUN:
            std::cout << "июнь"sv;
            break;
        case MONTH::JUL:
            std::cout << "июль"sv;
            break;
        case MONTH::AUG:
            std::cout << "август"sv;
            break;
        case MONTH::SEP:
            std::cout << "сентябрь"sv;
            break;
        case MONTH::OKT:
            std::cout << "октябрь"sv;
            break;
        case MONTH::NOV:
            std::cout << "ноябрь"sv;
            break;
        case MONTH::DEC:
            std::cout << "декабрь"sv;
            break;
        default:
            std::cerr << "неправильный месяц"sv;
            break;
    }
    
    std::cout << ' ' << 20 << date.GetDate().year << std::endl;
    std::cout << "------------------------------"sv << std::endl;
    std::cout << "Вода: "sv << date.GetWaterMeters().first << "-"sv << date.GetWaterMeters().second 
                          << "="sv << date.GetWaterMeters().first - date.GetWaterMeters().second << " x"sv
                          << TARIF_WATER << " = "sv << date.CalculateCostWater() << " руб."sv << std::endl;
    std::cout << "Газ: "sv << date.GetGasMeters().first << "-"sv << date.GetGasMeters().second
        << "="sv << date.GetGasMeters().first - date.GetGasMeters().second << " x"sv
        << TARIF_GAS << " = "sv << date.CalculateCostGas() << " руб."sv << std::endl;
    std::cout << "Свет: "sv << date.GetLightMeters().first << "-"sv << date.GetLightMeters().second
              << "="sv << date.GetLightMeters().first - date.GetLightMeters().second;
    if ((date.GetLightMeters().first - date.GetLightMeters().second) <= 150) {
        std::cout << " x"sv << TARIF_LIGHT_150 << " = "sv << date.CalculateCostLight() << " руб."sv << std::endl;
    }
    else {
        std::cout << " = "sv << "(150x"sv << TARIF_LIGHT_150 << ")+("sv << date.GetLightMeters().first - date.GetLightMeters().second - 150 << "x"sv
            << TARIF_LIGHT_800 << ") = "sv << date.CalculateCostLight() << " руб."sv << std::endl;
    }
    std::cout << "Квартплата: "sv << TARIF_RENT << " руб."sv << std::endl;
    std::cout << "Вывоз мусора: "sv << TARIF_GARBAGE << " руб."sv << std::endl;
    std::cout << "------------------------------"sv << std::endl;
    std::cout << "Итого за коммунальные услуги: "sv << date.CalculateCostWater() + date.CalculateCostGas() + date.CalculateCostLight()
                                                     + date.CalculateCostRent() + date.CalculateCostGarbage() << " руб."sv << std::endl;
}
