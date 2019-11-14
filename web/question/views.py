from django.utils import timezone
from django.shortcuts import render
from .models import Question
from answer.models import Answer

# Create your views here.

def index(request, user = "ser"):
    qst = Question.objects.all().order_by("date").reverse()
    return render(request, 'index.html', {'User':user, 'qst': qst})

def hot(request):
    qst = Question.objects.all()
    return render(request, 'hot.html', {'qst': qst})

def ask(request):
    return render(request, 'ask.html')

def qst_page(request, id):
    qst = Question.objects.filter(pk=id)
    q =list(qst)[0]
    # ans = Answer.objects.all().filter(qst=q)
    # print(ans[:5])
    # a = list(ans)
    ans = []
    for i in range(1,30):
        ans.append({
            'user': i,
            'qst' : q.pk,
            'text': 'text' + str(i),
            'date' : timezone.now()
        })
    return render(request, 'question.html', {'q': q, 'ans': ans})
