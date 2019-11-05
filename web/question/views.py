from django.shortcuts import render
from .models import Question
from answer.models import Answer

# Create your views here.

def index(request, user = "ser"):
    qst = Question.objects.all()
    return render(request, 'index.html', {'User':user, 'qst': qst})

def hot(request):
    qst = Question.objects.all()
    return render(request, 'index.html', {'qst': qst})

def ask(request):
    return render(request, 'ask.html')

def qst_page(request, id = 0):
    q = Question.objects.get(pk=id)
    ans = Answer.objects.all()
    return render(request, 'index.html', {'q': q, 'ans': ans})
