# PayService
## Консольное приложение, подсчитывающее стоимость оплаты коммунальных услуг в месяц
Основные функции: на основании введённых показаний приборов учёта (вода, газ, свет), а также постоянных показателей (квартплата, вывоз мусора) подсчитывает детально затраты в месяц на оплату коммунальных услуг.

Пример ввода:
```
Введите месяц и год оплаты (MM ГГ): 04 24
Введите показания приборов учёта
вода: 418
газ: 8590
свет: 12960
```
Пример вывода:
```
апрель 2024
------------------------------
Вода: 418-409=9 x74.04 = 666.36 руб.
Газ: 8590-8469=121 x6.02484 = 729.006 руб.
Свет: 12960-12803=157 = (150x3.93)+(7x4.98) = 624.36 руб.
Квартплата: 550.25 руб.
Вывоз мусора: 58.68 руб.
------------------------------
Итого за коммунальные услуги: 2628.66 руб.
```
Скрин работы приложения в окне консоли:
(https://github.com/kutuzzov/PayService/blob/main/ps.png)

## Инструкция по сборке проекта
