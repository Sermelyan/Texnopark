from django.urls import path

from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('hot', views.hot, name='hot'),
    path('ask', views.ask, name='ask'),
    path('question/<int:id>', views.qst_page, name='qst_page'),
]