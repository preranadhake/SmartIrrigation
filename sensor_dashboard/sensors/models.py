from django.db import models

class DHTData(models.Model):
    temperature = models.FloatField()
    humidity = models.FloatField()
    timestamp = models.DateTimeField(auto_now_add=True)

class SoilMoistureData(models.Model):
    moisture_level = models.IntegerField()
    timestamp = models.DateTimeField(auto_now_add=True)

class MotionData(models.Model):
    motion_detected = models.BooleanField()
    timestamp = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return "Motion Detected" if self.motion_detected else "No Motion"
