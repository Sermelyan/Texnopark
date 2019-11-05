from django.db import models
from user import models as user_models
from tag import models as tag_models

# Create your models here.

class Question(models.Model):
    title = models.CharField(max_length = 255, verbose_name="Название вопроса")
    text = models.TextField(verbose_name="Текст вопроса")
    date = models.DateTimeField(verbose_name="Дата создания")

    user = models.ForeignKey(
        user_models.User,
        on_delete = models.CASCADE,
    )
    tags = models.ManyToManyField(tag_models.Tag)

    objects = models.Manager

    def __str__(self):
        return self.title
    
    class Meta:
        verbose_name = 'Вопрос'
        verbose_name_plural = 'Вопросы'
