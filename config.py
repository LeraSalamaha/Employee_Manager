import sqlite3
import os

class DatabaseConfig:
    DB_PATH = "employees.db"
    
    @classmethod
    def get_connection(cls):
        try:
            conn = sqlite3.connect(cls.DB_PATH)
            conn.row_factory = sqlite3.Row  # Чтобы получать результаты как словари
            print(f"SQLite database connection established: {cls.DB_PATH}")
            return conn
        except sqlite3.Error as e:
            print(f"Database connection error: {e}")
            return None
    
    @classmethod
    def test_connection(cls):
        """Тестирует подключение к базе данных"""
        try:
            conn = cls.get_connection()
            if conn:
                conn.close()
                print("Database connection test successful!")
                return True
            return False
        except sqlite3.Error as e:
            print(f"Database setup error: {e}")
            return False