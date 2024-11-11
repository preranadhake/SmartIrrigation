# Generated by Django 5.1.2 on 2024-11-09 08:46

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('sensors', '0002_pumpstatushistory'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='pumpstatushistory',
            name='status',
        ),
        migrations.AddField(
            model_name='pumpstatushistory',
            name='is_pump_on',
            field=models.BooleanField(default=False),
        ),
        migrations.AlterField(
            model_name='pumpstatushistory',
            name='timestamp',
            field=models.DateTimeField(auto_now_add=True),
        ),
    ]