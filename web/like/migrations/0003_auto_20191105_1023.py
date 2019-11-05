# Generated by Django 2.2.7 on 2019-11-05 10:23

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('like', '0002_auto_20191105_1021'),
    ]

    operations = [
        migrations.AlterField(
            model_name='like',
            name='ans',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, to='answer.Answer'),
        ),
        migrations.AlterField(
            model_name='like',
            name='qst',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, to='question.Question'),
        ),
    ]
