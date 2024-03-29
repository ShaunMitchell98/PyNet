from PyNet.PyNet.PyNetwork import PyNetwork
from PyNet.PyNet.Settings import Settings
from PyNet.PyNet import ActivationFunctionType
from PyNet.PyNet import LogLevel
import tensorflow as tf
import TrainSession
import numpy as np
import re
import matplotlib.pyplot as plt
from LogPlotter import LogPlotter

fashion_mnist = tf.keras.datasets.fashion_mnist

(train_images, train_labels), (test_images, test_labels) = fashion_mnist.load_data()

class_names = ['T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat',
               'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle boot']

train_images = train_images / 255.0

test_images = test_images / 255.0

batch_sizes: list[int] = [1]
learning_rates: list[float] = [0.05]
momenta: list[float] = [0.7]
epochs: list[int] = [1]
numbers: list[int] = [50000]
dropoutRates: list[float] = [0.9]

for learning_rate in learning_rates:
    for batch_size in batch_sizes:
        for momentum in momenta:
            for dropoutRate in dropoutRates:
                for epoch in epochs:
                    for number in numbers:

                        logLevel: int = LogLevel.INFO

                        network = PyNetwork(logLevel, False)
                        #network.SetVariableLearning(0.04, 0.7, 1.05)
                        network.add_input_layer(784, 1, 1.0)
                        network.add_dense_layer(500, ActivationFunctionType.LOGISTIC, 0.9)
                        network.add_dense_layer(129, ActivationFunctionType.LOGISTIC, 0.9)
                        network.add_dense_layer(10, ActivationFunctionType.LOGISTIC, 0.9)

                        startNumber = 0
                        endNumber = 200

                        settings = Settings(logLevel, False, 0, learning_rate, batch_size, epoch, endNumber - startNumber, 0, momentum)
                        while endNumber <= number:
                            TrainSession.TrainSession(train_images, train_labels, network, startNumber,
                                                      endNumber, settings)

                            LogPlotter.PlotLog('Example Number: (.*), Loss is (.*)', 'Change_In_Loss.png', 'Change In Loss',
                                               'Loss')
                            LogPlotter.PlotLog('Example Number: (.*), Test Accuracy is (\\d*)', 'Change_In_Accuracy.png',
                                               'Change In Accuracy',
                                               'Accuracy (/100)')

                            for i in range(0, 3):
                                LogPlotter.PlotLog(f'Example Number: (.*), Bias for trainable layer {i} is (.*)\n',
                                                   f'Change_In_Bias_Layer{i}.png',
                                                   'Change In Bias',
                                                   'Bias')

                            LogPlotter.PlotLog(f'Example Number: (.*), Weights for trainable layer {i} are (.*)\n',
                                               f'Change in first weight.png',
                                               'Change in Weight',
                                               'Weight'
                                               )

                            startNumber = startNumber + 200
                            endNumber = endNumber + 200

                        network.destruct()

