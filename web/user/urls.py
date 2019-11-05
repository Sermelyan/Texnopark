from django.urls import path

from . import views

urlpatterns = [
    path('signin', views.sign_in, name='sign_in'),
    path('signup', views.sign_up, name='sign_up'),
    path('settings', views.settings, name='settings'),
    path('logout', views.logout, name='logout'),
]