from django.db import models

# Create your models here.

class User(models.Model):
    name = models.CharField(max_length = 255, verbose_name="Имя пользователя")
    date = models.DateTimeField(verbose_name="Дата создания")

    def __str__(self):
        return self.name
    
    class Meta:
        verbose_name = 'Пользователь'
        verbose_name_plural = 'Пользователи'