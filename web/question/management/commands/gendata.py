from django.core.management.base import BaseCommand, CommandError
from django.utils import timezone
import datetime
import random as rnd

from user.models import User
from tag.models import Tag
from question.models import Question
from answer.models import Answer
from like.models import Like

class Command(BaseCommand):
    help = 'Closes the specified poll for voting'

    def add_arguments(self, request):
        pass

    def handle(self, *args, **options):
        u = []
        for i in range(10):
            u.append(User(name="user{}".format(i), date=timezone.now()))
        
        for usr in u:
            usr.save()

        t = []
        for i in range(10):
            t.append( Tag(name="tag{}".format(i)) )
        
        for tag in t:
            tag.save()

        q = []
        i = 1
        for usr in u:
            q.append(
                Question(
                    title = "question{}".format(i),
                    text = "Lorem ipsum question from user: {}".format(usr),
                    date = timezone.now(),
                    user = usr
                )
            )
            i += 1

        for qst in q:
            qst.save()

        for qst in q:
            tags = qst.tags
            for i in range(3):
                tags.add(t[rnd.randint(0,9)])
            qst.save()
        
        a = []
        for que in q:
            for usr in u:
                a.append(
                    Answer(
                        text = "Lorem ipsum answer from user: {}".format(usr),
                        date = timezone.now(),
                        user = usr,
                        qst = que,
                    )
                )
        
        for ans in a:
            ans.save()