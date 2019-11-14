from django.shortcuts import render
from question.models import Question

# Create your views here.

def tag(request, name = "tag"):
    q = Question.objects.all()
    return render(request, 'tag.html', {'name': name, 'qst': q})