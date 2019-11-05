from django.urls import path

from . import views

urlpatterns = [
    path('tag/<str:name>', views.tagqst, name='tag'),
]