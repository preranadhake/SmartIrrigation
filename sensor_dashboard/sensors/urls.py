from django.urls import path
from . import views

urlpatterns = [
    path('dashboard/', views.dashboard, name='dashboard'),
    path('api/data/', views.get_latest_sensor_data, name='get_latest_sensor_data'),
    path('toggle_pump/', views.toggle_pump, name='toggle_pump'),
    path('pump_control/', views.pump_control, name='pump_control'),  # Add this line for pump control page

]
