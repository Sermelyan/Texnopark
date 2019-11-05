from django.utils import timezone
import datetime
import random as rnd

from user.models import User
from tag.models import Tag
from question.models import Question
from answer.models import Answer
from like.models import Like

u = []
for i in range(10):
    u.append(User(name="user{}".format(i), date=timezone.now()))
    u[i].save()

t = []
for i in range(10):
    t.append( Tag(name="tag{}".format(i)) )
    t[i].save()

q = []
for usr in u:
    for i in range(10):
        q.append(
            Question(
                title = "question{}".format(i),
                text = "Lorem ipsum hello from {}".format(i),
                date = timezone.now(),
                user = usr
            )
        )
        q[i].save()

for qst in q:
    tags = qst.tags
    for i in range(3):
       tags.add(t[rnd.randint(0,10)])
       qst.save()
    