from flask import Flask, request, render_template, redirect, send_from_directory, flash
import os
from werkzeug.utils import secure_filename
import mimetypes

# Сервер будет обрабатывать загрузку и воспроизведение звуковых файлов

UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'mp3', 'ogg', 'wav'}

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
app.config['SECRET_KEY'] = 'supersecretkey'

if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

def allowed_file(filename: str):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/', methods=['GET', 'POST'])
def index():
    # POST
    if request.method == 'POST':
        if 'file' not in request.files:
            flash('No file part')
            return redirect(request.url)
        file = request.files['file']
        if file.filename == '':
            flash('No selected file')
            return redirect(request.url)
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
            mimetype, _ = mimetypes.guess_type(filepath)
            if mimetype and mimetype.startswith('audio'):
                file.save(filepath)
                flash('File successfully uploaded')
            else:
                flash('Non-audio file detected')
            print(f"Uploaded file: {filename}")
            return redirect(request.url)
        else:
            flash('Invalid file type')
            return redirect(request.url)
    
    # GET
    files = os.listdir(app.config['UPLOAD_FOLDER'])
    print("Files on server:")
    for file in files:
        print(file)
    return render_template('index.html', files=files)

@app.route('/uploads/<filename>')
def uploaded_file(filename: str):
    return send_from_directory(app.config['UPLOAD_FOLDER'], filename)

if __name__ == '__main__':
    app.run(port=8888)
