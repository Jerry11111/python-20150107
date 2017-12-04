#!/usr/bin/python
import psycopg2

conn = psycopg2.connect(database="testdb", user="postgres", password="123456", host="127.0.0.1", port="5432")
print ('Opened database successfully')

# select
cur = conn.cursor()
cur.execute("SELECT user_id, user_name, create_timestamp FROM t_user")
rows = cur.fetchall()
print(type(rows))
print(rows)
for row in rows:
  print(type(row))
  print(row)

# INSERT
cur.execute("INSERT INTO public.t_user(user_name) VALUES ('test2')")
#cur.execute("INSERT INTO public.t_user(user_name) VALUES (%s)", ("test2"))#?TypeError: not all arguments converted during string formatting
conn.commit()
print("INSERT successfully")
conn.close()
