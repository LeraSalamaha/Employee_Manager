import sqlite3
import time
from config import DatabaseConfig

class EmployeeDatabase:
    def __init__(self):
        self.connection = DatabaseConfig.get_connection()
    
    def is_connected(self):
        """Проверяет, установлено ли соединение с БД"""
        return self.connection is not None
    
    def create_table(self) -> bool:
        """Создает таблицу сотрудников"""
        if not self.is_connected():
            print("Error: No database connection")
            return False
            
        cursor = None
        try:
            cursor = self.connection.cursor()
            cursor.execute("""
                CREATE TABLE IF NOT EXISTS employees (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    full_name TEXT NOT NULL,
                    birth_date TEXT NOT NULL,
                    gender TEXT NOT NULL CHECK (gender IN ('Male', 'Female')),
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    UNIQUE(full_name, birth_date)
                )
            """)
            
            # Создаем индексы для улучшения производительности
            cursor.execute("""
                CREATE INDEX IF NOT EXISTS idx_full_name ON employees (full_name)
            """)
            cursor.execute("""
                CREATE INDEX IF NOT EXISTS idx_gender ON employees (gender)
            """)
            cursor.execute("""
                CREATE INDEX IF NOT EXISTS idx_birth_date ON employees (birth_date)
            """)
            
            self.connection.commit()
            print("Table 'employees' created successfully with indexes")
            return True
        except sqlite3.Error as e:
            print(f"Error creating table: {e}")
            return False
        finally:
            if cursor:
                cursor.close()
    
    def insert_employee(self, employee) -> bool:
        """Вставляет одного сотрудника в базу данных"""
        if not self.is_connected():
            print("Error: No database connection")
            return False
            
        cursor = None
        try:
            cursor = self.connection.cursor()
            
            employee_data = employee.to_tuple()
            cursor.execute("""
                INSERT INTO employees (full_name, birth_date, gender)
                VALUES (?, ?, ?)
            """, employee_data)
            
            self.connection.commit()
            print(f"Employee '{employee.full_name}' added successfully")
            return True
        except sqlite3.IntegrityError:
            print(f"Error: Employee '{employee.full_name}' with birth date '{employee.birth_date}' already exists")
            return False
        except sqlite3.Error as e:
            print(f"Error inserting employee: {e}")
            return False
        finally:
            if cursor:
                cursor.close()
    
    def bulk_insert_employees(self, employees: list) -> bool:
        """Пакетная вставка сотрудников"""
        if not self.is_connected():
            print("Error: No database connection")
            return False
            
        cursor = None
        try:
            cursor = self.connection.cursor()
            
            # Преобразуем объекты Employee в кортежи
            data = [emp.to_tuple() for emp in employees]
            
            cursor.executemany("""
                INSERT OR IGNORE INTO employees (full_name, birth_date, gender)
                VALUES (?, ?, ?)
            """, data)
            
            self.connection.commit()
            inserted_count = cursor.rowcount
            print(f"Successfully inserted {inserted_count} employees")
            return True
        except sqlite3.Error as e:
            print(f"Error in bulk insert: {e}")
            return False
        finally:
            if cursor:
                cursor.close()
    
    def get_all_employees_sorted(self) -> list:
        """Получает всех сотрудников, отсортированных по ФИО"""
        if not self.is_connected():
            print("Error: No database connection")
            return []
            
        cursor = None
        try:
            cursor = self.connection.cursor()
            cursor.execute("""
                SELECT DISTINCT full_name, birth_date, gender
                FROM employees 
                ORDER BY full_name
            """)
            
            from employee import Employee
            employees = []
            for row in cursor.fetchall():
                emp = Employee.from_db_row(row)
                employees.append(emp)
            
            return employees
        except sqlite3.Error as e:
            print(f"Error fetching employees: {e}")
            return []
        finally:
            if cursor:
                cursor.close()
    
    def get_males_with_f_surname(self) -> tuple:
        """Получает мужчин с фамилией на 'F'"""
        if not self.is_connected():
            print("Error: No database connection")
            return [], 0
            
        cursor = None
        try:
            cursor = self.connection.cursor()
            start_time = time.time()
            
            cursor.execute("""
                SELECT full_name, birth_date, gender 
                FROM employees 
                WHERE gender = 'Male' AND full_name LIKE 'F%'
            """)
            
            execution_time = time.time() - start_time
            
            from employee import Employee
            employees = []
            for row in cursor.fetchall():
                emp = Employee.from_db_row(row)
                employees.append(emp)
            
            return employees, execution_time
        except sqlite3.Error as e:
            print(f"Error fetching employees: {e}")
            return [], 0
        finally:
            if cursor:
                cursor.close()
    
    def create_indexes(self) -> bool:
        """Создает индексы для оптимизации запросов"""
        if not self.is_connected():
            print("Error: No database connection")
            return False
            
        cursor = None
        try:
            cursor = self.connection.cursor()
            
            # Удаляем существующие индексы, если они есть
            indexes_to_create = [
                ("idx_gender_surname", "CREATE INDEX idx_gender_surname ON employees (gender, substr(full_name, 1, 1))"),
                ("idx_full_name_birth_date", "CREATE INDEX idx_full_name_birth_date ON employees (full_name, birth_date)"),
                ("idx_gender_full_name", "CREATE INDEX idx_gender_full_name ON employees (gender, full_name)")
            ]
            
            for index_name, create_sql in indexes_to_create:
                try:
                    cursor.execute(f"DROP INDEX IF EXISTS {index_name}")
                except sqlite3.Error:
                    pass
                
                cursor.execute(create_sql)
                print(f"Created index: {index_name}")
            
            self.connection.commit()
            print("All indexes created successfully")
            return True
        except sqlite3.Error as e:
            print(f"Error creating indexes: {e}")
            return False
        finally:
            if cursor:
                cursor.close()
    
    def get_table_info(self):
        """Получает информацию о таблице"""
        if not self.is_connected():
            return
            
        cursor = None
        try:
            cursor = self.connection.cursor()
            
            # Информация о таблице
            cursor.execute("SELECT COUNT(*) as count FROM employees")
            count = cursor.fetchone()[0]
            
            cursor.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='employees'")
            table_exists = cursor.fetchone() is not None
            
            print(f"Table 'employees' exists: {table_exists}")
            print(f"Total records: {count}")
            
        except sqlite3.Error as e:
            print(f"Error getting table info: {e}")
        finally:
            if cursor:
                cursor.close()
    
    def close(self):
        """Закрывает соединение с базой данных"""
        if self.connection:
            self.connection.close()
            print("Database connection closed")