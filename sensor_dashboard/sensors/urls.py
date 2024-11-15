from django.urls import path
from . import views

urlpatterns = [
    path('', views.dashboard, name='dashboard'),
    path('get_latest_sensor_data/', views.get_latest_sensor_data, name='get_latest_sensor_data'),
    path('get_pump_status/', views.get_pump_status, name='get_pump_status'),

    path('toggle_pump/', views.toggle_pump, name='toggle_pump'),
    path('pump_control/', views.pump_control, name='pump_control'), 

    # path('turn_pump_on/', views.turn_pump_on, name='turn_pump_on'),
    # path('turn_pump_off/', views.turn_pump_off, name='turn_pump_off'),

]
