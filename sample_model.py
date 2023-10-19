import torch
import timm

model = timm.models.mlp_mixer.mixer_b16_224()              

print(model)

torch.onnx.export(model, torch.randn(1,3,224,224), "mlpmixer.onnx")