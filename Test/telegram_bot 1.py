import datetime
from pyrogram import Client
from loguru import logger
from sqlalchemy import create_engine, Column, Integer, DateTime
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker
import time

Base = declarative_base()

class User(Base):
    __tablename__ = 'users'
    id = Column(Integer, primary_key=True)
    registration_time = Column(DateTime, default=datetime.datetime.utcnow)

    @staticmethod
    def users_registered_today(session):
        today = datetime.datetime.utcnow().date()
        return session.query(User).filter(User.registration_time >= today).count()

DB_URL = 'postgresql+asyncpg://username:password@localhost/dbname'
engine = create_engine(DB_URL, echo=True)

Base.metadata.create_all(engine)
Session = sessionmaker(bind=engine)

def handle_message(client, message):
    session = Session()
    user = session.query(User).filter_by(id=message.from_user.id).first()

    if not user:
        user = User(id=message.from_user.id)
        session.add(user)
        session.commit()
        logger.info(f"New user registered: {user.id}")

    if message.text and "Хорошего дня" in message.text:
        client.send_message(
            chat_id=message.from_user.id,
            text="Скоро вернусь с новым материалом!"
        )

    session.close()

def users_today(client, message):
    session = Session()
    count = User.users_registered_today(session)
    client.send_message(
        chat_id=message.from_user.id,
        text=f"Количество зарегистрированных пользователей за сегодня: {count}"
    )
    session.close()

def main():
    app = Client("my_account")

    app.on_message()(handle_message)
    app.on_command("users_today")(users_today)

    app.start()

    start_time = datetime.datetime.utcnow()

    while True:
        now = datetime.datetime.utcnow()
        delta = now - start_time

        if delta.seconds >= 600:
            app.send_message(chat_id="my_account", text="Добрый день!")
        if delta.seconds >= 5400: 
            app.send_message(chat_id="my_account", text="Подготовила для вас материал")
        if delta.seconds >= 5405:
            app.send_photo(chat_id="my_account", photo="https://upload.wikimedia.org/wikipedia/commons/e/e8/%D0%9F%D1%80%D0%B8%D0%BC%D0%B5%D1%80.png", caption="Отправка фото")
        if delta.seconds >= 7200:
            user_history = app.get_chat_history(chat_id="my_account", limit=10)
            trigger_found = any("Хорошего дня" in msg.text for msg in user_history.messages)
            if not trigger_found:
                app.send_message(chat_id="my_account", text="Скоро вернусь с новым материалом!")

        time.sleep(10)

if __name__ == '__main__':
    main('TOKEN').serve()
