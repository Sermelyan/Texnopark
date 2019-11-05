from django.shortcuts import render

# Create your views here.

def tagqst(request, name = "tag"):
    return render(request, 'index.html')