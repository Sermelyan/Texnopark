from django.db import models
from user import models as user_models
from question import models as qst_models
from answer import models as ans_models

# Create your models here.

class Like(models.Model):
    status = models.BooleanField(verbose_name="Плюс/Минус")
    
    user = models.ForeignKey(
        user_models.User,
        on_delete = models.CASCADE,
    )

    qst = models.ForeignKey(
        qst_models.Question,
        on_delete = models.CASCADE,
        blank = True,
        null = True,
    )
    
    ans = models.ForeignKey(
        ans_models.Answer,
        on_delete = models.CASCADE,
        blank = True,
        null = True,
    )

    def __str__(self):
        return self.user.__str__
    
    class Meta:
        verbose_name = 'Лайк'
        verbose_name_plural = 'Лайки'
