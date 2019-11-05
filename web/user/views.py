from django.shortcuts import render

# Create your views here.

def sign_in(request):
    return render(request, 'signin.html')

def sign_up(request):
    return render(request, 'signup.html')

def settings(request):
    return render(request, 'settings.html')

def logout(request):
    return render(request, 'index.html')
