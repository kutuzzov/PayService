# PayService
## Консольное приложение, подсчитывающее оплату коммунальных услуг за месяц
Основные функции:
- на основании введённых показаний приборов учёта (вода, газ, свет), а также постоянных показателей (квартплата, вывоз мусора) подсчитывает детально затраты в месяц на оплату коммунальных услуг, в частности расчёт оплаты электроэнергии многоуровневый в зависимости от потреблённого количества. Удобно пользователям, кто не может пользоваться подсчётами в личных кабинетах на сайтах поставщиков услуг, например арендующим жильё, чтобы скинуть показания и расчёты арендодателям;
- сохраняет предыдущие значения показаний для расчёта потреблённых услуг за отчётный месяц (рядом с исполняемым файлом создаётся файл meters_data.txt, куда перезаписываются значения);
- вывод в наглядном формате позволяет сохранить расчёты в заметках, избранном мессенджеров, например Telegram и др.;
- в связи с редким обновлением тарифов поставщиками услуг (1-2 раза в год) последние выставляются вручную в файле tariffs.h, кто желает может дополнительно добавить функционал установления тарифов через консоль.

Update: добавлен код для телеграм-бота на python, позволяющего взаимодействовать с программой через мессенджер.

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

![](https://github.com/kutuzzov/PayService/blob/main/images/ps.png)

Скрины работы бота в Telegram:

<img src="images/photo_2025-04-04_09-59-14.jpg" alt="Пример изображения" width="200"> <img src="images/photo_2025-04-04_09-59-15.jpg" alt="Пример изображения" width="200"> <img src="images/photo_2025-04-04_09-59-16.jpg" alt="Пример изображения" width="200">

## Сборка и установка
Сборка с помощью любой IDE либо сборка из командной строки

## Системные требования
Компилятор С++ с поддержкой стандарта C++17 или новее

(с) [@kutuzzov](https://github.com/kutuzzov/)
