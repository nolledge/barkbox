FROM python:3-alpine
RUN mkdir /app
COPY . /app
WORKDIR /app
RUN pip install -r requirements.txt
ENTRYPOINT ["python", "-u", "tg_bot.py"]
