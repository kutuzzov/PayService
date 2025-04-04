from telegram import Update, InlineKeyboardButton, InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove
from telegram.ext import ApplicationBuilder, CommandHandler, MessageHandler, filters, ConversationHandler, ContextTypes, CallbackQueryHandler
import subprocess

# Определяем состояния для ConversationHandler
SELECTING_DATE, SELECTING_READINGS = range(2)

# Словарь для хранения данных пользователя
user_data = {}

# Клавиатура с кнопками /start и /cancel
reply_keyboard = [
    ["Старт", "Отмена"]
]
reply_markup = ReplyKeyboardMarkup(reply_keyboard, resize_keyboard=True)

# Команда /start для начала диалога
async def start(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    # Удаляем клавиатуру с кнопками /start и /cancel
    await update.message.reply_text(
        "Добро пожаловать! 📊 Выберите период оплаты.",
        reply_markup=ReplyKeyboardRemove()
    )
    
    # Создаем Inline-кнопки для выбора месяца и года
    keyboard = [
        [InlineKeyboardButton("Январь 2025", callback_data="01 25")],
        [InlineKeyboardButton("Февраль 2025", callback_data="02 25")],
        [InlineKeyboardButton("Март 2025", callback_data="03 25")],
        [InlineKeyboardButton("Апрель 2025", callback_data="04 25")],
        [InlineKeyboardButton("Май 2025", callback_data="05 25")],
        [InlineKeyboardButton("Июнь 2025", callback_data="06 25")],
        [InlineKeyboardButton("Июль 2025", callback_data="07 25")],
        [InlineKeyboardButton("Август 2025", callback_data="08 25")],
        [InlineKeyboardButton("Сентябрь 2025", callback_data="09 25")],
        [InlineKeyboardButton("Октябрь 2025", callback_data="10 25")],
        [InlineKeyboardButton("Ноябрь 2025", callback_data="11 25")],
        [InlineKeyboardButton("Декабрь 2025", callback_data="12 25")],
        [InlineKeyboardButton("Январь 2026", callback_data="01 26")],
        [InlineKeyboardButton("Февраль 2026", callback_data="02 26")]
    ]
    reply_markup = InlineKeyboardMarkup(keyboard)
    
    await update.message.reply_text(
        "📆 Выберите период оплаты:", reply_markup=reply_markup
    )
    return SELECTING_DATE

# Обработка нажатия кнопки для выбора месяца и года
async def date_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    query = update.callback_query
    await query.answer()
    
    # Сохраняем выбранный месяц и год
    user_data['month'], user_data['year'] = query.data.split()
    
    # Переходим к выбору типа показаний
    return await show_readings_buttons(update, context)

# Показать кнопки для выбора типа показаний
async def show_readings_buttons(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    # Формируем список кнопок, исключая уже введенные типы показаний
    buttons = []
    if 'water' not in user_data:
        buttons.append([InlineKeyboardButton("Вода 🚰", callback_data="water")])
    if 'gas' not in user_data:
        buttons.append([InlineKeyboardButton("Газ ⛽️", callback_data="gas")])
    if 'electricity' not in user_data:
        buttons.append([InlineKeyboardButton("Свет 💡", callback_data="electricity")])
    
    reply_markup = InlineKeyboardMarkup(buttons)
    
    if buttons:
        # Если есть оставшиеся типы показаний, отправляем новое сообщение с кнопками
        if update.callback_query:
            await update.callback_query.edit_message_text(
                "Внесите показания:", reply_markup=reply_markup
            )
        else:
            await update.message.reply_text(
                "Внесите показания счётчиков:", reply_markup=reply_markup
            )
    else:
        # Если все данные введены, переходим к обработке
        return await process_data(update, context)
    
    return SELECTING_READINGS

# Обработка нажатия кнопки для выбора типа показаний
async def readings_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    query = update.callback_query
    await query.answer()
    
    # Сохраняем выбранный тип показаний
    user_data['current_type'] = query.data
    
    # Запрашиваем значение для выбранного типа
    if query.data == "water":
        await query.edit_message_text("Введите показания воды:")
    elif query.data == "gas":
        await query.edit_message_text("Введите показания газа:")
    elif query.data == "electricity":
        await query.edit_message_text("Введите показания света:")
    
    return SELECTING_READINGS

# Обработка ввода показаний
async def input_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    user_input = update.message.text.strip()
    
    # Проверка, что был выбран тип показаний
    if 'current_type' not in user_data:
        await update.message.reply_text(
            "Ошибка: Вы не выбрали тип показаний. Пожалуйста, выберите тип показаний из предложенных кнопок."
        )
        return SELECTING_READINGS
    
    # Проверка, что введено число
    if not user_input.isdigit():
        await update.message.reply_text(
            "Неверный формат. Введите показания как число:"
        )
        return SELECTING_READINGS
    
    # Сохраняем введенные данные
    if user_data['current_type'] == "water":
        user_data['water'] = user_input
    elif user_data['current_type'] == "gas":
        user_data['gas'] = user_input
    elif user_data['current_type'] == "electricity":
        user_data['electricity'] = user_input
    
    # Удаляем current_type после сохранения данных
    del user_data['current_type']
    
    # Показываем оставшиеся кнопки для выбора типа показаний
    return await show_readings_buttons(update, context)

# Обработка данных и отправка в PayService.exe
async def process_data(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    # Формируем строку данных для отправки в PayService.exe
    data_to_send = (
        f"{user_data['month']} {user_data['year']}\n"
        f"{user_data['water']}\n"
        f"{user_data['gas']}\n"
        f"{user_data['electricity']}\n"
    )
    
    try:
        # Запускаем программу PayService.exe и отправляем данные через stdin
        process = subprocess.Popen(
            ["PayService.exe"],  # Убедитесь, что PayService.exe находится в той же директории или укажите полный путь
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True  # Для работы с текстовыми данными
        )
        
        # Отправляем данные в программу и получаем результат
        stdout, stderr = process.communicate(input=data_to_send)
        
        if process.returncode == 0:
            # Если программа завершилась успешно, отправляем результат пользователю
            await update.message.reply_text(f"{stdout}")
        else:
            # Если произошла ошибка, отправляем сообщение об ошибке
            await update.message.reply_text(f"❌ Ошибка при обработке данных:\n{stderr}")
    
    except Exception as e:
        # Обработка исключений (например, если PayService.exe не найден)
        await update.message.reply_text(f"❌ Произошла ошибка: {str(e)}")
    
    # После завершения диалога показываем кнопки /start и /cancel
    await update.message.reply_text(
        "Для начала нового диалога нажмите /start.", reply_markup=reply_markup
    )
    return ConversationHandler.END

# Обработка команды /cancel для отмены диалога
async def cancel(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    # Возвращаем клавиатуру с кнопками /start и /cancel
    await update.message.reply_text(
        "❌ Диалог отменён.", reply_markup=reply_markup
    )
    return ConversationHandler.END

def main():
    # Создаем объект Application с токеном бота
    application = ApplicationBuilder().token("ВАШ ТОКЕН").build()

    # Создаем ConversationHandler для управления диалогом
    conv_handler = ConversationHandler(
        entry_points=[CommandHandler('start', start)],
        states={
            SELECTING_DATE: [CallbackQueryHandler(date_handler)],
            SELECTING_READINGS: [
                CallbackQueryHandler(readings_handler),
                MessageHandler(filters.TEXT & ~filters.COMMAND, input_handler)
            ],
        },
        fallbacks=[CommandHandler('cancel', cancel)],
        # Явно указываем параметры per_*
        per_chat=True,  # Отслеживать диалог для каждого чата
        per_user=True,   # Отслеживать диалог для каждого пользователя
        per_message=False  # Не отслеживать диалог для каждого сообщения
    )

    # Добавляем обработчик в приложение
    application.add_handler(conv_handler)

    # Запускаем бота
    application.run_polling()

if __name__ == "__main__":
    main()
