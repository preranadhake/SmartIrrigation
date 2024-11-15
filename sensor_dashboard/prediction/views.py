import os
import numpy as np
from tensorflow.keras.models import load_model
from tensorflow.keras.preprocessing.image import img_to_array, load_img
from django.shortcuts import render
from django.core.files.storage import default_storage


# Load model
model_path = os.path.join(os.path.dirname(__file__), 'best_model.keras')
model = load_model(model_path)
print(os.path.exists(model_path)) 
class_names = ['Apple___Apple_scab', 'Apple___Black_rot', 'Apple___healthy', 
               'Cherry_(including_sour)___healthy', 'Cherry_(including_sour)___Powdery_mildew',
                'Corn_(maize)___Common_rust_', 'Corn_(maize)___healthy', 'Corn_(maize)___Northern_Leaf_Blight',
               'Grape___Black_rot', 'Grape___Esca_(Black_Measles)', 'Grape___healthy',
               'Peach___Bacterial_spot', 'Peach___healthy', 
               'Pepper,_bell___Bacterial_spot', 'Pepper,_bell___healthy',
               'Potato___Early_blight', 'Potato___healthy', 'Potato___Late_blight',
               'Strawberry___healthy', 'Strawberry___Leaf_scorch', 
               'Tomato___Bacterial_spot', 'Tomato___Early_blight', 'Tomato___healthy', 'Tomato___Spider_mites Two-spotted_spider_mite'
               ]  # Update this list with actual class names

def predict_disease(image_path):
    image = load_img(image_path, target_size=(128, 128))
    image = img_to_array(image)
    image = np.expand_dims(image, axis=0) / 255.0
    prediction = model.predict(image)
    predicted_class = np.argmax(prediction, axis=1)
    return class_names[predicted_class[0]]

def upload_and_predict(request):
    if request.method == 'POST' and request.FILES['image']:
        image = request.FILES['image']
        image_path = default_storage.save('tmp/' + image.name, image)
        prediction = predict_disease(image_path)
        return render(request, 'prediction/result.html', {'prediction': prediction})
    return render(request, 'prediction/upload.html')
