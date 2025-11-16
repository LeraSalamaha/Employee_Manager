import sys
import random
from datetime import datetime, timedelta
from database import EmployeeDatabase
from employee import Employee
from config import DatabaseConfig

class EmployeeManager:
    def __init__(self):
        self.db = EmployeeDatabase()
    
    def check_database_connection(self):
        """Проверяет подключение к базе данных"""
        if not self.db.is_connected():
            print("\n" + "="*60)
            print("DATABASE CONNECTION ERROR")
            print("="*60)
            print("Cannot connect to database.")
            
            print("\nTesting connection...")
            if DatabaseConfig.test_connection():
                print("Connection test successful! Reinitializing...")
                self.db = EmployeeDatabase()
                return self.db.is_connected()
            else:
                return False
        return True
    
    def show_help(self):
        """Показывает справку по использованию программы"""
        help_text = """
Employee Management System (SQLite Version)

Usage:
    python main.py [mode] [arguments]

Modes:
    1 - Create employees table
    2 - Add new employee: python main.py 2 "Full Name" "YYYY-MM-DD" "Gender"
    3 - Show all employees sorted by name
    4 - Generate test data (1,000,000 + 100 special records)
    5 - Search males with 'F' surname (with timing)
    6 - Optimize database indexes
    help - Show this help message

Examples:
    python main.py 1
    python main.py 2 "Ivanov Petr Sergeevich" "1990-05-15" "Male"
    python main.py 3
    python main.py 4
    python main.py 5
    python main.py 6

Interactive mode:
    Run without arguments to use interactive menu

Note: Uses SQLite database (employees.db) - no server setup required!
        """
        print(help_text)
    
    def run_mode_1(self):
        """Режим 1: Создание таблицы"""
        if not self.check_database_connection():
            return
            
        print("Creating employees table...")
        if self.db.create_table():
            print("Table created successfully!")
            # Показываем информацию о таблице
            self.db.get_table_info()
        else:
            print("Failed to create table!")
    
    def run_mode_2(self, args):
        """Режим 2: Добавление сотрудника"""
        if not self.check_database_connection():
            return
            
        if len(args) < 3:
            print("Error: Insufficient arguments for mode 2")
            print("Usage: python main.py 2 \"Full Name\" \"YYYY-MM-DD\" \"Gender\"")
            return
        
        full_name = args[0]
        birth_date = args[1]
        gender = args[2]
        
        # Нормализация пола
        if gender.lower() in ['m', 'male', 'муж', 'мужской']:
            gender = 'Male'
        elif gender.lower() in ['f', 'female', 'жен', 'женский']:
            gender = 'Female'
        else:
            print("Error: Gender must be 'Male' or 'Female'")
            return
        
        employee = Employee(full_name, birth_date, gender)
        
        if employee.validate():
            if self.db.insert_employee(employee):
                print("Employee added successfully!")
            else:
                print("Failed to add employee!")
        else:
            print("Invalid employee data!")
    
    def run_mode_3(self):
        """Режим 3: Показать всех сотрудников"""
        if not self.check_database_connection():
            return
            
        print("Fetching all employees...")
        employees = self.db.get_all_employees_sorted()
        
        if not employees:
            print("No employees found!")
            return
        
        print("\n{:<40} {:<12} {:<8} {:<8}".format(
            "Full Name", "Birth Date", "Gender", "Age"
        ))
        print("-" * 80)
        
        for emp in employees:
            age = emp.calculate_age()
            print("{:<40} {:<12} {:<8} {:<8}".format(
                emp.full_name, emp.birth_date, emp.gender, age
            ))
        
        print(f"\nTotal employees: {len(employees)}")
    
    def run_mode_4(self):
        """Режим 4: Генерация тестовых данных"""
        if not self.check_database_connection():
            return
            
        print("Generating test data...")
        print("Note: This may take a while for 1,000,000 records...")
        
        # Списки для генерации имен
        first_names = ['John', 'Michael', 'David', 'James', 'Robert', 'Mary', 'Jennifer', 'Linda', 'Patricia', 'Elizabeth']
        last_names = ['Smith', 'Johnson', 'Williams', 'Brown', 'Jones', 'Miller', 'Davis', 'Garcia', 'Rodriguez', 'Wilson']
        
        employees = []
        
        # Генерируем 1,000,000 записей (для теста можно уменьшить количество)
        record_count = 1000000
        print(f"Generating {record_count:,} random employees...")
        
        for i in range(record_count):
            first_name = random.choice(first_names)
            last_name = random.choice(last_names)
            middle_name = random.choice(['Alexander', 'Thomas', 'Charles', 'Christopher', 'Matthew'])
            
            full_name = f"{last_name} {first_name} {middle_name}"
            
            # Случайная дата рождения от 1950 до 2005
            start_date = datetime(1950, 1, 1)
            end_date = datetime(2005, 12, 31)
            random_date = start_date + timedelta(
                seconds=random.randint(0, int((end_date - start_date).total_seconds()))
            )
            birth_date = random_date.strftime('%Y-%m-%d')
            
            # Равномерное распределение пола
            gender = 'Male' if i % 2 == 0 else 'Female'
            
            employees.append(Employee(full_name, birth_date, gender))
            
            # Прогресс
            if (i + 1) % 100000 == 0:
                print(f"Generated {i + 1:,} employees...")
        
        # Добавляем 100 мужчин с фамилией на F
        print("Generating 100 male employees with 'F' surname...")
        f_surnames = ['Fisher', 'Fletcher', 'Ford', 'Foster', 'Fox', 'Franklin', 'Frazier', 'Freeman', 'French', 'Fuller']
        
        for i in range(100):
            first_name = random.choice(first_names)
            last_name = random.choice(f_surnames)
            middle_name = random.choice(['Andrew', 'Benjamin', 'Daniel', 'Edward', 'George'])
            
            full_name = f"{last_name} {first_name} {middle_name}"
            
            start_date = datetime(1950, 1, 1)
            end_date = datetime(2005, 12, 31)
            random_date = start_date + timedelta(
                seconds=random.randint(0, int((end_date - start_date).total_seconds()))
            )
            birth_date = random_date.strftime('%Y-%m-%d')
            
            employees.append(Employee(full_name, birth_date, 'Male'))
        
        # Пакетная вставка
        print("Inserting data into database...")
        if self.db.bulk_insert_employees(employees):
            print("Test data generated successfully!")
            self.db.get_table_info()
        else:
            print("Failed to generate test data!")
    
    def run_mode_5(self):
        """Режим 5: Поиск мужчин с фамилией на F с замером времени"""
        if not self.check_database_connection():
            return
            
        print("Searching for males with 'F' surname...")
        
        employees, execution_time = self.db.get_males_with_f_surname()
        
        print(f"\nSearch executed in {execution_time:.4f} seconds")
        print(f"Found {len(employees)} employees")
        
        # Показываем первые 10 результатов
        if employees:
            print("\nFirst 10 results:")
            print("{:<40} {:<12} {:<8}".format("Full Name", "Birth Date", "Gender"))
            print("-" * 60)
            
            for emp in employees[:10]:
                print("{:<40} {:<12} {:<8}".format(emp.full_name, emp.birth_date, emp.gender))
    
    def run_mode_6(self):
        """Режим 6: Оптимизация базы данных"""
        if not self.check_database_connection():
            return
            
        print("Optimizing database with indexes...")
        
        # Сначала замеряем производительность до оптимизации
        print("\nPerformance before optimization:")
        employees, time_before = self.db.get_males_with_f_surname()
        print(f"Search time: {time_before:.4f} seconds")
        print(f"Records found: {len(employees)}")
        
        # Создаем индексы
        if self.db.create_indexes():
            print("\nPerformance after optimization:")
            employees, time_after = self.db.get_males_with_f_surname()
            print(f"Search time: {time_after:.4f} seconds")
            print(f"Records found: {len(employees)}")
            
            if time_before > 0:
                improvement = ((time_before - time_after) / time_before) * 100
                print(f"Performance improvement: {improvement:+.1f}%")
        else:
            print("Failed to optimize database!")
    
    def interactive_mode(self):
        """Интерактивный режим"""
        while True:
            print("\n" + "="*50)
            print("Employee Management System (SQLite)")
            print("="*50)
            print("1. Create employees table")
            print("2. Add new employee")
            print("3. Show all employees")
            print("4. Generate test data")
            print("5. Search males with 'F' surname")
            print("6. Optimize database")
            print("7. Database info")
            print("8. Help")
            print("0. Exit")
            print("-"*50)
            
            choice = input("Select mode (0-8): ").strip()
            
            if choice == '0':
                print("Goodbye!")
                break
            elif choice == '1':
                self.run_mode_1()
            elif choice == '2':
                self.add_employee_interactive()
            elif choice == '3':
                self.run_mode_3()
            elif choice == '4':
                self.run_mode_4()
            elif choice == '5':
                self.run_mode_5()
            elif choice == '6':
                self.run_mode_6()
            elif choice == '7':
                self.db.get_table_info()
            elif choice == '8':
                self.show_help()
            else:
                print("Invalid choice! Please try again.")
    
    def add_employee_interactive(self):
        """Интерактивное добавление сотрудника"""
        if not self.check_database_connection():
            return
            
        print("\nAdd New Employee")
        print("-" * 30)
        
        full_name = input("Full Name: ").strip()
        birth_date = input("Birth Date (YYYY-MM-DD): ").strip()
        gender = input("Gender (Male/Female): ").strip()
        
        # Нормализация пола
        if gender.lower() in ['m', 'male', 'муж', 'мужской']:
            gender = 'Male'
        elif gender.lower() in ['f', 'female', 'жен', 'женский']:
            gender = 'Female'
        else:
            print("Error: Gender must be 'Male' or 'Female'")
            return
        
        employee = Employee(full_name, birth_date, gender)
        
        if employee.validate():
            if self.db.insert_employee(employee):
                print("Employee added successfully!")
            else:
                print("Failed to add employee!")
        else:
            print("Invalid employee data!")

def main():
    print("Employee Management System (SQLite)")
    print("Initializing...")
    
    # тестируем подключение к базе данных
    if not DatabaseConfig.test_connection():
        print("\nFailed to initialize database connection.")
        return
    
    manager = EmployeeManager()
    
    if len(sys.argv) == 1:
        # Интерактивный режим
        manager.interactive_mode()
    elif len(sys.argv) >= 2:
        # Режим с аргументами командной строки
        mode = sys.argv[1]
        
        if mode == '1':
            manager.run_mode_1()
        elif mode == '2':
            if len(sys.argv) >= 5:
                manager.run_mode_2(sys.argv[2:5])
            else:
                print("Error: Insufficient arguments for mode 2")
                print("Usage: python main.py 2 \"Full Name\" \"YYYY-MM-DD\" \"Gender\"")
        elif mode == '3':
            manager.run_mode_3()
        elif mode == '4':
            manager.run_mode_4()
        elif mode == '5':
            manager.run_mode_5()
        elif mode == '6':
            manager.run_mode_6()
        elif mode in ['help', '--help', '-h']:
            manager.show_help()
        else:
            print(f"Error: Unknown mode '{mode}'")
            manager.show_help()
        
        # Закрываем соединение с БД
        manager.db.close()
    else:
        manager.show_help()
        manager.db.close()

if __name__ == "__main__":
    main()