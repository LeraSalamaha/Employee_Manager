from datetime import datetime, date

class Employee:
    def __init__(self, full_name: str, birth_date: str, gender: str):
        self.full_name = full_name
        self.birth_date = birth_date
        self.gender = gender
        
    def calculate_age(self) -> int:
        """Рассчитывает полный возраст сотрудника"""
        try:
            birth_date = datetime.strptime(self.birth_date, '%Y-%m-%d').date()
            today = date.today()
            age = today.year - birth_date.year
            
            # Проверяем, был ли уже день рождения в этом году
            if today.month < birth_date.month or (today.month == birth_date.month and today.day < birth_date.day):
                age -= 1
                
            return age
        except ValueError as e:
            print(f"Error calculating age: {e}")
            return 0
    
    def validate(self) -> bool:
        """Валидация данных сотрудника"""
        if not self.full_name or len(self.full_name.strip()) == 0:
            print("Error: Full name cannot be empty")
            return False
            
        try:
            datetime.strptime(self.birth_date, '%Y-%m-%d')
        except ValueError:
            print("Error: Invalid birth date format. Use YYYY-MM-DD")
            return False
            
        if self.gender.lower() not in ['male', 'female', 'мужской', 'женский']:
            print("Error: Gender must be 'male' or 'female'")
            return False
            
        return True
    
    def to_tuple(self):
        """Преобразует сотрудника в кортеж для вставки в БД"""
        gender = 'Male' if self.gender.lower() in ['male', 'мужской'] else 'Female'
        return (self.full_name, self.birth_date, gender)
    
    @staticmethod
    def from_db_row(row):
        """Создает объект Employee из строки БД"""
        birth_date_str = row['birth_date'] if isinstance(row['birth_date'], str) else row['birth_date']
        return Employee(row['full_name'], birth_date_str, row['gender'])
    
    def __str__(self):
        age = self.calculate_age()
        return f"{self.full_name} | {self.birth_date} | {self.gender} | {age} years"