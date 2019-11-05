from django.db import models
from user import models as user_models
from question import models as qst_models


# Create your models here.

class Answer(models.Model):
    text = models.TextField(verbose_name="Ответ")
    date = models.DateTimeField(verbose_name="Дата создания")

    user = models.ForeignKey(
        user_models.User,
        on_delete = models.CASCADE,
    )

    qst = models.ForeignKey(
        qst_models.Question,
        on_delete = models.CASCADE,
    )

    objects = models.Manager

    def __str__(self):
        return 'Hello'
    
    class Meta:
        verbose_name = 'Ответ'
        verbose_name_plural = 'Ответы'
