; ModuleID = 'simple-loop-unswitch.c'
source_filename = "simple-loop-unswitch.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %4 = bitcast i32* %2 to i8*
  call void @llvm.lifetime.start.p0i8(i64 4, i8* %4) #2
  store i32 0, i32* %2, align 4, !tbaa !3
  %5 = bitcast i32* %3 to i8*
  call void @llvm.lifetime.start.p0i8(i64 4, i8* %5) #2
  store i32 0, i32* %3, align 4, !tbaa !3
  br label %6

6:                                                ; preds = %19, %0
  %7 = load i32, i32* %3, align 4, !tbaa !3
  %8 = icmp slt i32 %7, 10
  br i1 %8, label %11, label %9

9:                                                ; preds = %6
  %10 = bitcast i32* %3 to i8*
  call void @llvm.lifetime.end.p0i8(i64 4, i8* %10) #2
  br label %22

11:                                               ; preds = %6
  %12 = load i32, i32* %2, align 4, !tbaa !3
  %13 = add nsw i32 %12, 1
  store i32 %13, i32* %2, align 4, !tbaa !3
  %14 = load i32, i32* %3, align 4, !tbaa !3
  %15 = load i32, i32* %2, align 4, !tbaa !3
  %16 = icmp eq i32 %14, %15
  br i1 %16, label %17, label %18

17:                                               ; preds = %11
  store i32 0, i32* %2, align 4, !tbaa !3
  br label %18

18:                                               ; preds = %17, %11
  br label %19

19:                                               ; preds = %18
  %20 = load i32, i32* %3, align 4, !tbaa !3
  %21 = add nsw i32 %20, 1
  store i32 %21, i32* %3, align 4, !tbaa !3
  br label %6, !llvm.loop !7

22:                                               ; preds = %9
  %23 = bitcast i32* %2 to i8*
  call void @llvm.lifetime.end.p0i8(i64 4, i8* %23) #2
  ret i32 0
}

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #1

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.end.p0i8(i64 immarg, i8* nocapture) #1

attributes #0 = { nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { argmemonly nofree nosync nounwind willreturn }
attributes #2 = { nounwind }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"uwtable", i32 1}
!2 = !{!"clang version 13.0.1"}
!3 = !{!4, !4, i64 0}
!4 = !{!"int", !5, i64 0}
!5 = !{!"omnipotent char", !6, i64 0}
!6 = !{!"Simple C/C++ TBAA"}
!7 = distinct !{!7, !8, !9}
!8 = !{!"llvm.loop.mustprogress"}
!9 = !{!"llvm.loop.unroll.disable"}
